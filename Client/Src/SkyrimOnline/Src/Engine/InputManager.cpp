/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "InputManager.h"
#include <Directx/myIDirect3DDevice9.h>

namespace SkyrimOnline
{
	namespace Engine
	{
		//--------------------------------------------------------------------------------
		InputManager::InputManager(InputManager::Listener& pListener)
			:mListener(pListener), mRun(true)
		{
			// Valeur de retour des méthodes utilisées, permet la gestion des erreurs
			HRESULT result;

			// Création de l'objet DirectInput
			result = DirectInput8Create(
				myIDirect3DDevice9::GetInstance()->GetHinstance(),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&mDirectInput,
				NULL
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("DirectInput8Create Failed.");
			}

			result  = mDirectInput->CreateDevice(
				GUID_SysKeyboard,
				&mKeyboard,
				NULL
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("Keyboard CreateDevice Failed.");
			}

			mKeyboard->SetDataFormat(
				&c_dfDIKeyboard
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("Mouse SetDataFormat Failed.");
			}

			result = mKeyboard->SetCooperativeLevel(
				myIDirect3DDevice9::GetInstance()->GetWindow(),
				DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("Keyboard SetCooperativeLevel Failed.");
			}

			if(mKeyboard)
			{
				Log::GetInstance()->Debug("Keyboard acquired !");
				mKeyboard->Acquire();
			}

			result  = mDirectInput->CreateDevice(
				GUID_SysMouse,
				&mMouse,
				NULL
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("Mouse CreateDevice Failed.");
			}

			result = mMouse->SetDataFormat(
				&c_dfDIMouse
				);

			if(FAILED(result))
			{
				Log::GetInstance()->Error("Mouse SetDataFormat Failed.");
			}

			if(mMouse)
				mMouse->Acquire();

			for(auto i = 0 ; i < 256; ++i)
				mKeys[i] = 0;

			mThread = new boost::thread(std::bind(&InputManager::Run, this));

			Log::GetInstance()->Debug("InputManager::InputManager()");
		}
		//--------------------------------------------------------------------------------
		InputManager::~InputManager()
		{
			mRun = false;
			mThread->join();
			delete mThread;
			mMouse->Release();
			mKeyboard->Release();
			Log::GetInstance()->Debug("InputManager::~InputManager()");
		}
		//--------------------------------------------------------------------------------
		void InputManager::Run()
		{
			while(mRun)
			{
				boost::this_thread::yield();

				DIMOUSESTATE tmp;
				char buffer[256];

				if(FAILED(mKeyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer)))
				{
					mKeyboard->Acquire();
					return;
				}

				if(FAILED(mMouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&tmp)))
				{
					mMouse->Acquire();
					return;
				}

				for(auto i = 0 ; i < 256; ++i)
				{
					char state = buffer[i];
					if(state != mKeys[i])
					{
						mKeys[i] = buffer[i];
						if(buffer[i] & 0x80)
						{
							Event e;
							e.key = i;
							e.keyboard = true;
							e.pressed = true;
							e.time = clock();
							mBufferedInputs.push(e);
						}
						else
						{
							Event e;
							e.key = i;
							e.keyboard = true;
							e.pressed = false;
							e.time = clock();
							mBufferedInputs.push(e);
						}
					}
				}
				for(auto i = 0; i < 4; ++i)
				{
					char state = tmp.rgbButtons[i];
					if(state != mMouseState[i])
					{
						mMouseState[i] = state;
						if(state & 0x80)
						{
							Event e;
							e.key = i;
							e.keyboard = false;
							e.pressed = true;
							e.time = clock();
							mBufferedInputs.push(e);
						}
						else
						{
							Event e;
							e.key = i;
							e.keyboard = false;
							e.pressed = false;
							e.time = clock();
							mBufferedInputs.push(e);
						}
					}
				}
			}
		}
		//--------------------------------------------------------------------------------
		void InputManager::Update()
		{
			Event e;
			while(!mBufferedInputs.empty())
				while(mBufferedInputs.try_pop(e))
				{
					if((clock() - e.time) < 1000)
					{
						if(e.keyboard == true)
						{
							if(e.pressed == true)
								mListener.OnPress(e.key);
							else
								mListener.OnRelease(e.key);
						}
						else
						{
							if(e.pressed == true)
								mListener.OnMousePress(e.key);
							else
								mListener.OnMouseRelease(e.key);
						}
					}
				}

			POINT pos;
			GetCursorPos(&pos);
			mListener.OnMouseMove(pos.x,pos.y,0);
		}
		//--------------------------------------------------------------------------------
	}
}