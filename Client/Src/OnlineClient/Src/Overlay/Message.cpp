//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

#include "stdafx.h"
#include "Message.h"

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		Message::Message(MyGUI::Gui* pUI)
			:mUI(pUI)
		{
			mWindow = mUI->createWidget<MyGUI::Window>("WindowC", mUI->getViewWidth() - mUI->getViewWidth()/2 - 250,
				mUI->getViewHeight()/4 - 80,500,160,
				MyGUI::Align::Default, "Overlapped", "");
			mWindow->setCaption("Error");
			mWindow->setSnap(true);
			mWindow->setProperty("Widget_Alpha","1");

			mText = mWindow->createWidget<MyGUI::StaticText>("StaticText", 10, 20, mWindow->getSize().width-10, 100, ::MyGUI::Align::Default, "");
			mOk = mWindow->createWidget<MyGUI::Button>("Button", mWindow->getSize().width/2-40, mWindow->getSize().height/2+10, 80, 26, ::MyGUI::Align::Default, "");
			mOk->setCaption("Ok");
			mOk->eventMouseButtonClick = MyGUI::newDelegate(this,&Message::Handle_Click);
		}
		//--------------------------------------------------------------------------------
		Message::~Message()
		{
		}
		//--------------------------------------------------------------------------------
		void	Message::Hide()
		{
			mWindow->setVisible(false);
		}
		//--------------------------------------------------------------------------------
		void	Message::Show()
		{
			mWindow->setVisible(true);
		}
		//--------------------------------------------------------------------------------
		void	Message::SetVisible(bool v)
		{
			if(v)
				MyGUI::LayerManager::getInstance().upLayerItem(mWindow);
			mWindow->setVisible(v);
		}
		//--------------------------------------------------------------------------------
		bool	Message::IsVisible()
		{
			return mWindow->isVisible();
		}
		//--------------------------------------------------------------------------------
		void	Message::SetCaption(const std::string& pText)
		{
			mText->setCaption(pText);
		}
		//--------------------------------------------------------------------------------
		void	Message::Update(double e)
		{
		}
		//--------------------------------------------------------------------------------
		void	Message::Handle_Click(MyGUI::WidgetPtr _widget)
		{
			Hide();
		}
		//--------------------------------------------------------------------------------
	}
}