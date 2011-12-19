//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "ShardList.h"
#include <Mod.h>
#include <Network/Session.h>
#include <Network/Packet.h>

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		ShardList::ShardList(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			mText = mUI->createWidget<MyGUI::StaticText>("StaticText",
				mUI->getViewWidth()*0.25,
				mUI->getViewHeight()*0.3 - 40,
				mUI->getViewWidth()*0.5,
				26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListText");
			mText->setCaption("Shard list");

			mList = mUI->createWidget<MyGUI::List>("List",
				mUI->getViewWidth()*0.25,
				mUI->getViewHeight()*0.3,
				mUI->getViewWidth()*0.5,
				mUI->getViewHeight()*0.4,
				MyGUI::Align::Default, "Overlapped",
				"ShardListList");

			mButton = mUI->createWidget<MyGUI::Button>("Button",
				mUI->getViewWidth()*0.65,
				mUI->getViewHeight()*0.7 + 10,
				mUI->getViewWidth()*0.10,
				26,
				MyGUI::Align::Default, "Overlapped",
				"ShardListButton");
			mButton->setCaption("Enter");

			mButton->eventMouseButtonClick = MyGUI::newDelegate(this, &ShardList::Handle_Click);

			mList->setInheritsAlpha(true);
		}
		//--------------------------------------------------------------------------------
		ShardList::~ShardList()
		{
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Hide()
		{
			SetVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Show()
		{
			SetVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	ShardList::SetVisible(bool v)
		{
			mList->setVisible(v);
			mText->setVisible(v);
			mButton->setVisible(v);
		}
		//--------------------------------------------------------------------------------
		bool	ShardList::IsVisible()
		{
			return mList->isVisible();
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Log(const MyGUI::UString& str)
		{
			mMessagesMutex.lock();

			mMessages.push_back(str);

			mMessagesMutex.unlock();
		}
		//--------------------------------------------------------------------------------
		void	ShardList::_Log()
		{
			mMessagesMutex.lock();

			while(!mMessages.empty())
			{
				mList->addItem(mMessages.front());
				mMessages.pop_front();
			}

			mMessagesMutex.unlock();
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Update(double e)
		{
			_Log();
		}
		//--------------------------------------------------------------------------------
		void	ShardList::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			if(mList->getIndexSelected() == MyGUI::ITEM_NONE)
			{
			}
			else
			{
				Packet packet;
				packet.Opcode = CMSG_SHARD_PICK;
				packet.Push(mList->getItem(mList->getIndexSelected()).asUTF8());
				Mod::GetInstance().GetSession().Write(packet);
			}
		}
		//--------------------------------------------------------------------------------
	}
}