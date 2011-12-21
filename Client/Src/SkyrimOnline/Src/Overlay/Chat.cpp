/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "Chat.h"
#include <Network/Packet.h>
#include <Mod.h>
#include <Network/Session.h>

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		Chat::Chat(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			MyGUI::LayoutManager::getInstance().loadLayout("chat.xml");
			mEdit = mUI->findWidget<MyGUI::Edit>("Chat_Edit");
			mList = mUI->findWidget<MyGUI::List>("Chat_List");

			MyGUI::InputManager::getInstance().setKeyFocusWidget(mUI->findWidget<MyGUI::Edit>("Chat_Edit"));

			mEdit->eventEditSelectAccept = MyGUI::newDelegate(this,&Chat::Handle_Click);

			mList->setNeedKeyFocus(false);
		}
		//--------------------------------------------------------------------------------
		Chat::~Chat()
		{
		}
		//--------------------------------------------------------------------------------
		void	Chat::Hide()
		{
			mEdit->setVisible(false);
			mList->setVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	Chat::Show()
		{
			mEdit->setVisible(true);
			mList->setVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	Chat::SetVisible(bool v)
		{
			mEdit->setVisible(v);
			mList->setVisible(v);
		}
		//--------------------------------------------------------------------------------
		bool	Chat::IsVisible()
		{
			return mList->isVisible();
		}

		//--------------------------------------------------------------------------------
		void	Chat::Update(double e)
		{
			mMessagesMutex.lock();

			for(auto it = mMessages.begin(); it != mMessages.end(); ++it)
				this->_Log(it->first, it->second);

			mMessages.clear();

			mMessagesMutex.unlock();
		}
		//--------------------------------------------------------------------------------
		void	Chat::Log(const MyGUI::UString& str, const MyGUI::UString& color)
		{
			Log::GetInstance()->Debug(std::string("Chat: ") + str.asUTF8());

			mMessagesMutex.lock();

			mMessages.push_back(std::make_pair(str,color));

			mMessagesMutex.unlock();
		}
		//--------------------------------------------------------------------------------
		void	Chat::_Log(const MyGUI::UString& str, const MyGUI::UString& color)
		{
			while(mList->getItemCount() > 200)
				mList->removeItemAt(0);

			std::wstring tmp;

			std::vector<std::wstring> lines;
			lines.clear();

			MyGUI::IFont* font = MyGUI::FontManager::getInstance().getByName(MyGUI::FontManager::getInstance().getDefaultFont());

			int ctr = 0;

			for(size_t i = 0; i < str.size(); i++)
			{
				if(ctr + font->getGlyphInfo((int)str[i])->width > mList->getWidth() - 35)
				{
					ctr = 0;

					if(str[i] != L' ')
						tmp.push_back(L'-');
					else
						while(str[i] == L' ' && i < str.size()){i++;}

						lines.push_back(tmp);
						tmp.clear();
				}

				tmp.push_back(str[i]);

				ctr += font->getGlyphInfo((int)str[i])->width;

				if (i >= str.size() - 1)
				{
					ctr = 0;
					lines.push_back(tmp);
					tmp.clear();
				}
			}

			for (unsigned int i = 0 ; i < lines.size() ; i++)
			{
				if (i == 0)
				{
					std::wstring toAdd;
					toAdd += lines[i].substr(0, lines[i].find(L":") + 1);
					toAdd += color;
					toAdd += lines[i].substr(lines[i].find(L":") + 1, lines[i].size());

					mList->addItem(toAdd);
				}
				else
				{
					std::wstring toAdd = color;
					toAdd += lines[i];
					mList->addItem(toAdd);
				}
			}

			mList->beginToItemLast();
		}
		//--------------------------------------------------------------------------------
		void	Chat::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			MyGUI::UString& str = mEdit->getOnlyText();
			if(str.size() != 0)
			{
				Network::Session& session = Mod::GetInstance().GetSession();
				if(session.IsOnline())
				{
					Packet packet;
					packet.Opcode = CMSG_CHAT;
					packet.Push(str.asUTF8());
					session.Write(packet);
				}
				else
				{
					Log("You are not connected !","#FF0000");
				}

				mEdit->setTextSelect(0, mEdit->getTextLength());
				mEdit->deleteTextSelect();
			}
		}
		//--------------------------------------------------------------------------------
	}
}