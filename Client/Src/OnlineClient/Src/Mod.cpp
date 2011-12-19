#include "stdafx.h"
#include "Mod.h"
#include <Overlay/Login.h>
#include <Overlay/Chat.h>
#include <Overlay/FriendList.h>
#include <Overlay/ShardList.h>
#include <Overlay/Message.h>

namespace SkyrimOnline
{
	//--------------------------------------------------------------------------------
	Mod* Mod::instance = nullptr;
	//--------------------------------------------------------------------------------
	Mod::Mod()
		:mUI(Overlay::Interface::GetInstance()), mArena(nullptr),mInput(*this),mMode(true)
	{
		Log::GetInstance()->Debug("Mod()");
		mUI->Acquire();
		mSession = Network::Session::Create();
		mSession->Start();
		mPlayer.SetSession(mSession);
		SwitchMode(); // Enter UI mode
		Network::Session::Init(); // Init callbacks
		Log::GetInstance()->Debug("Mod() -e");
	}
	//--------------------------------------------------------------------------------
	Mod::~Mod()
	{
		Log::GetInstance()->Debug("~Mod()");
		if(mSession)
			mSession->close();
		delete mArena;
		mUI->Reset();
	}
	//--------------------------------------------------------------------------------
	void Mod::SwitchMode()
	{
		Log::GetInstance()->Debug("SwitchMode()");
		mMode = !mMode;
		if(mMode)
		{
			// In game mode -> enable controls
			::Game::EnablePlayerControls(true,true,true,true,true,true,true,true,1);
			mUI->SetCursor(false);
		}
		else
		{
			// In UI mode -> disable controls
			::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
			mUI->SetCursor(true);
		}
	}
	//--------------------------------------------------------------------------------
	void Mod::OnConnectionLost()
	{
		if(mState.IsState(Game::StateManager::LOGIN))
		{
			if(mUI)
			{
				mUI->GetMessage()->SetCaption("Username and/or password mismatch ! \nCreate an account on http://skyrim-online.com");
				mUI->GetMessage()->Show();
				mUI->GetLogin()->Show();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void Mod::OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		if(!mMode)
			mUI->MouseMove(x,y,z);
	}
	//--------------------------------------------------------------------------------
	void Mod::OnPress(BYTE code)
	{
		if(!mMode)
			mUI->Inject(code,true);
		if(mState.IsState(Game::StateManager::IN_GAME))
		{
			mWaveManager.OnPress(code);
		}
	}
	//--------------------------------------------------------------------------------
	void Mod::OnRelease(BYTE code)
	{
		if(!mMode)
			mUI->Inject(code,false);
		if(mState.IsState(Game::StateManager::IN_GAME))
		{
			if(code == DIK_NUMPAD4)
			{
				if(mArena)
				{
					delete mArena;
					mArena = nullptr;
				}
				else
				{
					mArena = new Game::ArenaBuilder;
				}
			}
			else if(code == DIK_F3)
			{
				SwitchMode();
			}
			mWaveManager.OnRelease(code);
		}
	}
	//--------------------------------------------------------------------------------
	void Mod::OnMousePress(BYTE code)
	{
		if(!mMode)
			mUI->InjectMouse(code,true);
	}
	//--------------------------------------------------------------------------------
	void Mod::OnMouseRelease(BYTE code)
	{
		if(!mMode)
			mUI->InjectMouse(code,false);
	}
	//--------------------------------------------------------------------------------
	void Mod::Run()
	{
		while (1)
		{
			SetRendering(clock());
			float delta = mTimer.elapsed();
			mTimer.restart();

			mInput.Update();

			if(mState.IsState(Game::StateManager::LOGIN) || mState.IsState(Game::StateManager::SHARD_LIST))
			{
				::Game::DisablePlayerControls(true,true,true,true,true,true,true,true,1);
				mUI->SetCursor(true);
			}
			else if(mState.IsState(Game::StateManager::IN_GAME))
			{
				mTimeManager.Update(delta);
				mWeatherManager.Update(delta);
				mWaveManager.Run();
				mPlayer.Update(delta);

				if(mPlayer.IsDead())
					mWaveManager.Clear();

				mManager.Update(delta);
			}

			if(mSession)
				mSession->Run();

			Wait(0);
		}
	}
	//--------------------------------------------------------------------------------
	Mod& Mod::GetInstance()
	{
		if(instance == nullptr)
			instance = new Mod;
		return *instance;
	}
	//--------------------------------------------------------------------------------
	bool Mod::Exists()
	{
		return instance != nullptr;
	}
	//--------------------------------------------------------------------------------
	void Mod::Kill()
	{
		delete instance;
		instance = nullptr;
	}
	//--------------------------------------------------------------------------------
	Game::CharacterManager& Mod::GetCharacterManager()
	{
		return mManager;
	}
	//--------------------------------------------------------------------------------
	Network::Session& Mod::GetSession()
	{
		return *mSession;
	}
	//--------------------------------------------------------------------------------
	Overlay::Interface& Mod::GetInterface()
	{
		return *mUI;
	}
	//--------------------------------------------------------------------------------
	Game::StateManager& Mod::GetStateManager()
	{
		return mState;
	}
	//--------------------------------------------------------------------------------
	Game::TimeManager& Mod::GetTimeManager()
	{
		return mTimeManager;
	}
	//--------------------------------------------------------------------------------
	Game::WeatherManager& Mod::GetWeatherManager()
	{
		return mWeatherManager;
	}
	//--------------------------------------------------------------------------------
	Game::AssetManager& Mod::GetAssetManager()
	{
		return mAssets;
	}
	//--------------------------------------------------------------------------------
	unsigned int Mod::GetRendering()
	{
		return mRendering;
	}
	//--------------------------------------------------------------------------------
	void Mod::SetRendering(unsigned int rendering)
	{
		mRendering = rendering;
	}
	//--------------------------------------------------------------------------------
	void Mod::SetUser(const std::string& user)
	{
		mUsername = user;
	}
	//--------------------------------------------------------------------------------
	std::string Mod::GetUser()
	{
		return mUsername;
	}
	//--------------------------------------------------------------------------------
	void Mod::EnterState(Game::StateManager::Enum pState)
	{
		mState.SetState(pState);
		switch(pState)
		{
		case Game::StateManager::SHARD_LIST:
			mUI->GetMessage()->Hide();
			mUI->GetShardList()->Show();
			mUI->GetLogin()->Hide();
			break;
		case Game::StateManager::IN_GAME:
			mUI->GetShardList()->Hide();
			mUI->GetChat()->Show();
			mUI->GetFriendList()->Show();
			SwitchMode();
			break;
		}
	}
	//--------------------------------------------------------------------------------
	void Mod::Login(const std::string& user, const std::string& pass)
	{
		mUI->GetMessage()->Show();
		if(!mSession->IsOnline())
		{
			mUI->GetMessage()->SetCaption("Connecting...");
			mSession->Start();
		}
		if(mSession->IsOnline())
		{
			mUI->GetLogin()->Hide();

			mUI->GetMessage()->SetCaption("Authenticating and negotiating RSA.");

			Packet data;
			data.Opcode = CMSG_AUTHENTICATION;
			data.Push(user);
			data.Push(pass);

			mSession->Write(data);
		}
		else
		{
			mUI->GetMessage()->SetCaption("Server offline");
		}
	}
	//--------------------------------------------------------------------------------
}