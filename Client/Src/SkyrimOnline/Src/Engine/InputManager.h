/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

namespace SkyrimOnline
{
	namespace Engine
	{
		class InputManager
		{
		public:

			struct Listener
			{
				virtual void OnPress(BYTE code) = 0;
				virtual void OnRelease(BYTE code) = 0;
				virtual void OnMousePress(BYTE code) = 0;
				virtual void OnMouseRelease(BYTE code) = 0;
				virtual void OnMouseMove(unsigned int x, unsigned int y, unsigned int z) = 0;
			};

			InputManager(Listener& pListener);
			~InputManager();

			void Run();
			void Update();

		private:

			struct Event
			{
				bool pressed;
				bool keyboard;
				BYTE key;
				clock_t time;
			};

			bool mRun;
			unsigned int mX, mY;
			char mKeys[256];
			LPDIRECTINPUT8 mDirectInput;
			LPDIRECTINPUTDEVICE8 mKeyboard;
			LPDIRECTINPUTDEVICE8 mMouse;
			char mMouseState[4];
			Listener& mListener;
			Concurrency::concurrent_queue<Event> mBufferedInputs;
			boost::thread* mThread;
		};
	}
}