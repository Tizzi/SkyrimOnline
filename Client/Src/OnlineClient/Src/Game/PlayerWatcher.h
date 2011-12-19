#pragma once

#include <Network/Session.h>
#include <Game/Character.h>

namespace SkyrimOnline
{
	namespace Game
	{
		class PlayerWatcher
		{
		public:

			PlayerWatcher();

			void Update(float);

			void SetSession(Network::Session* pSession);

			bool IsDead();

		private:

			Network::Session* mSession;
			Character mPlayer;
			bool mSentInfos;
			float mTimer;
			bool mMount;
		};
	}
}