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