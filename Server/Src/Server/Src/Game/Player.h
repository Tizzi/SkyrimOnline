#pragma once

#include <System/Vector3.h>

namespace Skyrim{
	namespace Network
	{
		class Session;
	}
	namespace Game
	{
		class Mount;
		class Player
		{
		public:

			Player();
			~Player();

			unsigned int race();
			unsigned int level();
			unsigned int sex();
			bool HasMount();
			Mount* GetMount();
			void SetMount(unsigned int pMountID);

		private:

			friend class Network::Session;

			Mount* mMount;
			System::Vector3 mPosition, mRotation;
			unsigned int mRace, mLevel, mSex;
			float mElapsed;
		};
	}
}