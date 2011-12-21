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
#include "FriendList.h"

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		FriendList::FriendList(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			mWindow = mUI->createWidget<MyGUI::Window>("WindowC", mUI->getViewWidth() - mUI->getViewWidth() * 0.15,
				mUI->getViewHeight()/3,mUI->getViewWidth()*0.15,mUI->getViewHeight() * 0.33,
				MyGUI::Align::Default, "Overlapped", "FriendListWindow");
			mWindow->setCaption("Friend list");
			mWindow->setSnap(true);
			mWindow->setProperty("Widget_Alpha","0.7");

			mEdit = mWindow->createWidget<MyGUI::Edit>("Edit", 0, mWindow->getSize().height-70, mWindow->getSize().width-40, 26, ::MyGUI::Align::Default, "FriendListEdit");
			mEdit->setInheritsAlpha(true);
			mWindow->createWidget<MyGUI::Edit>("Button", mWindow->getSize().width-40, mWindow->getSize().height-70, 26, 26, ::MyGUI::Align::Default, "FriendListButton")->setCaption("+");
			mList = mWindow->createWidget<MyGUI::List>("List",
				0,
				0,
				mWindow->getSize().width-5,
				mWindow->getSize().height-80,
				MyGUI::Align::Default,
				"FriendListList");
			mList->setInheritsAlpha(true);
		}
		//--------------------------------------------------------------------------------
		FriendList::~FriendList()
		{
		}
		//--------------------------------------------------------------------------------
		void	FriendList::Hide()
		{
			mWindow->setVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	FriendList::Show()
		{
			mWindow->setVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	FriendList::SetVisible(bool v)
		{
			mWindow->setVisible(v);
		}
		//--------------------------------------------------------------------------------
		bool	FriendList::IsVisible()
		{
			return mWindow->isVisible();
		}

		//--------------------------------------------------------------------------------
		void	FriendList::Update(double e)
		{
		}
		//--------------------------------------------------------------------------------
		void	FriendList::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			MyGUI::UString& str = ((MyGUI::EditPtr)_widget)->getOnlyText();

			((MyGUI::EditPtr)_widget)->setTextSelect(0, ((MyGUI::EditPtr)_widget)->getTextLength());
			((MyGUI::EditPtr)_widget)->deleteTextSelect();
		}
		//--------------------------------------------------------------------------------
	}
}