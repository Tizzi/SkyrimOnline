//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "Login.h"
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		Login::Login(MyGUI::Gui* pUI)
			:mUI(pUI), mVisible(false)
		{
			mUserText = mUI->createWidget<MyGUI::StaticText>("StaticText", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2-43,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped", "LoginEditUserText");
			mUserText->setCaption("Username : ");

			mEditUser = mUI->createWidget<MyGUI::Edit>("Edit", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2-13,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped", "LoginEditUser");

			mPassText = mUI->createWidget<MyGUI::StaticText>("StaticText", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2+30,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped", "LoginEditPassText");
			mPassText->setCaption("Password : ");

			mEditPass = mUI->createWidget<MyGUI::Edit>("Edit", mUI->getViewWidth() * 0.4,
				mUI->getViewHeight()/2+60,mUI->getViewWidth()*0.2,26,
				MyGUI::Align::Default, "Overlapped", "LoginEditPass");
			mEditPass->setEditPassword(true);

			mSubmit = mUI->createWidget<MyGUI::Button>("Button", mUI->getViewWidth() * 0.45,
				mUI->getViewHeight()/2+115,mUI->getViewWidth()*0.1,26,
				MyGUI::Align::Default, "Overlapped", "LoginButton");
			mSubmit->setCaption("Login");

			MyGUI::InputManager::getInstance().setKeyFocusWidget(mEditUser);

			mSubmit->eventMouseButtonClick = MyGUI::newDelegate(this,&Login::Handle_Click);
		}
		//--------------------------------------------------------------------------------
		Login::~Login()
		{
		}
		//--------------------------------------------------------------------------------
		void	Login::Hide()
		{
			SetVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	Login::Show()
		{
			SetVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	Login::SetVisible(bool pVisible)
		{
			mVisible = pVisible;

			mEditUser->setEnabled(pVisible);
			mEditPass->setEnabled(pVisible);
			mSubmit->setEnabled(pVisible);

			mEditUser->setVisible(pVisible);
			mEditPass->setVisible(pVisible);
			mPassText->setVisible(pVisible);
			mUserText->setVisible(pVisible);
			mSubmit->setVisible(pVisible);
		}
		//--------------------------------------------------------------------------------
		bool	Login::IsVisible()
		{
			return mVisible;
		}
		//--------------------------------------------------------------------------------
		void	Login::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			std::string lLogin		= mEditUser->getOnlyText().asUTF8();
			std::string lPassword	= mEditPass->getOnlyText().asUTF8();

			Mod::GetInstance().SetUser(lLogin);
			Mod::GetInstance().Login(lLogin, lPassword);
		}
		//--------------------------------------------------------------------------------
	}
}