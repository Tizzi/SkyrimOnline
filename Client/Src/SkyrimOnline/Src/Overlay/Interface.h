/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <Directx/myIDirect3DDevice9.h>

namespace SkyrimOnline
{
	namespace Overlay
	{
		class Chat;
		class FriendList;
		class Login;
		class ShardList;
		class Message;

		class Interface
		{
		public:

			void Setup();

			void Inject(BYTE key, bool pressed);
			void InjectMouse(BYTE key, bool pressed);
			void MouseMove(unsigned int x, unsigned int y, unsigned int z);

			void SetCursor(bool pVisible);
			bool IsCursorVisible();

			void OnRender(myIDirect3DDevice9* pDevice);
			void OnLostDevice(myIDirect3DDevice9* pDevice);

			Chat* GetChat();
			FriendList* GetFriendList();
			Login* GetLogin();
			ShardList* GetShardList();
			Message* GetMessage();

			static Interface* GetInstance();

			void Reset();
			void Acquire();

		private:

			Interface();
			~Interface();

			int x,y;
			MyGUI::DirectXPlatform* mPlatform;
			MyGUI::Gui*				mUI;
			std::string mRootMedia;

			Chat* mChat;
			FriendList* mFriendList;
			Login* mLogin;
			ShardList * mShardList;
			Message* mMessageBox;

			static Interface* instance;

			boost::signals::connection mRender,mReset;
		};
	}
}