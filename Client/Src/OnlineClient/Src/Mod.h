#pragma once

#include <Game/PlayerWatcher.h>
#include <Game/WaveManager.h>
#include <Game/ArenaBuilder.h>
#include <Game/StateManager.h>
#include <Game/CharacterManager.h>
#include <Game/TimeManager.h>
#include <Game/WeatherManager.h>
#include <Game/AssetManager.h>

#include <Overlay/Interface.h>
#include <Engine/InputManager.h>
#include <Network/Session.h>

namespace SkyrimOnline
{
	class Mod
		: public Engine::InputManager::Listener
	{
	public:

		Mod();
		~Mod();
		void Run();

		void OnPress(BYTE code);
		void OnRelease(BYTE code);
		void OnMousePress(BYTE code);
		void OnMouseRelease(BYTE code);
		void OnMouseMove(unsigned int x, unsigned int y, unsigned int z);

		void OnConnectionLost();

		static Mod& GetInstance();
		static void Kill();
		static bool Exists();

		Game::CharacterManager& GetCharacterManager();
		Network::Session& GetSession();
		Overlay::Interface& GetInterface();
		Game::StateManager& GetStateManager();
		Game::TimeManager& GetTimeManager();
		Game::WeatherManager& GetWeatherManager();
		Game::AssetManager& GetAssetManager();
		unsigned int GetRendering();
		void SetRendering(unsigned int);

		void SetUser(const std::string& user);

		void Login(const std::string& user, const std::string& pass);

		std::string GetUser();

		void SwitchMode();

		void EnterState(Game::StateManager::Enum);

	private:

		//< Note order is important, gui first !
		Overlay::Interface* mUI;
		Engine::InputManager mInput;
		bool mMode;
		unsigned int mRendering;
		boost::shared_ptr<boost::asio::io_service> mIoService;

		//< Alright now start initializing gameplay stuff
		Game::PlayerWatcher mPlayer;
		Game::CharacterManager mManager;
		Game::WaveManager mWaveManager;
		Game::ArenaBuilder* mArena;
		Game::StateManager mState;
		Game::TimeManager mTimeManager;
		Game::WeatherManager mWeatherManager;
		Game::AssetManager mAssets;

		std::string mUsername;

		Network::Session* mSession;

		boost::timer mTimer;

		static Mod* instance;
	};
}