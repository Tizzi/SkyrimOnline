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

#pragma once

namespace SkyrimOnline
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		/// @brief A chat interface for the client
		//--------------------------------------------------------------------------------
		class Login
		{
			public:

				//--------------------------------------------------------------------------------
				/// @brief Hides the chat
				//--------------------------------------------------------------------------------
				void	Hide();

				//--------------------------------------------------------------------------------
				/// @brief Shows the chat
				//--------------------------------------------------------------------------------
				void	Show();

				//--------------------------------------------------------------------------------
				/// @brief Set the console's visibility
				/// @param n self explanatory
				//--------------------------------------------------------------------------------
				void	SetVisible(bool isVisible);

				//--------------------------------------------------------------------------------
				/// @brief Is the console visible or not
				/// @return visibility
				//--------------------------------------------------------------------------------
				bool	IsVisible();

				bool Setup(){return true;}

				void Destroy(){}

				//--------------------------------------------------------------------------------
				/// @brief Handles an edit box accept event.
				/// @param _widget The widget firing the event.
				//--------------------------------------------------------------------------------
				void Handle_Click(MyGUI::WidgetPtr _widget);

				//--------------------------------------------------------------------------------
				/// @brief Constructor, do not call
				//--------------------------------------------------------------------------------
				Login(MyGUI::Gui*);

				//--------------------------------------------------------------------------------
				/// @brief Destructor, do not call
				//--------------------------------------------------------------------------------
				~Login();

			private:
				bool mVisible;

				//--------------------------------------------------------------------------------
				/// @brief The login's edit box
				//--------------------------------------------------------------------------------
				MyGUI::EditPtr			mEditUser;
				MyGUI::EditPtr			mEditPass;

				MyGUI::StaticTextPtr	mUserText;
				MyGUI::StaticTextPtr	mPassText;

				MyGUI::ButtonPtr		mSubmit;

				MyGUI::Gui*				mUI;
		};
	}
}