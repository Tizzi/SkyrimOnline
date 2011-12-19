#pragma once

#include <System/Vector3.h>

namespace Skyrim{
	namespace Network
	{
		class Session;
	}
	namespace Game
	{
		class Mount
		{
		public:

			Mount(unsigned int pSkyrimID);

			unsigned int GetSkyrimId();

		private:

			friend class Network::Session;

			System::Vector3 mPosition, mRotation;
			unsigned int mSkyrimID;
		};
	}
}