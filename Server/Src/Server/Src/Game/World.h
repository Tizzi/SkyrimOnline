#pragma once

#include <Network/Session.h>
#include <Game/TimeManager.h>
#include <Game/WeatherManager.h>

namespace Skyrim{
	namespace Game
	{
		class World
		{
		public:

			World(const std::string&, bool);

			void Run();

			void Add(Network::Session::pointer pPlayer);
			void Remove(Network::Session::pointer pPlayer);

			void DispatchPlayerMoveAndLook(Network::Session::pointer pPlayer);
			void DispatchToAll(Network::Packet&);
			void DispatchToAllButMe(Network::Packet&, Network::Session::pointer pPlayer);

			bool IsMarkedForDelete();
			std::string GetName();

			unsigned int Count();

		protected:

			void SendTimeSync(Network::Session::pointer pPlayer);
			void SendWeatherSync(Network::Session::pointer pPlayer);

		private:

			bool mPersistant;
			std::string mName;
			std::deque<Network::Session::pointer> mSessions;
			boost::mutex mGuard, mReleaseGuard;
			boost::timer mTimer;
			boost::thread* mWorldThread;

			// Actual gameplay related
			TimeManager mTimeManager;
			WeatherManager mWeatherManager;
		};
	}
}