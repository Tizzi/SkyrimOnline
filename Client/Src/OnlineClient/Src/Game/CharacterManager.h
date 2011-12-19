#pragma once

#include "RemotePlayer.h"

namespace SkyrimOnline
{
	namespace Game
	{
		class __declspec(dllexport) CharacterManager
		{
		public:

			CharacterManager();
			~CharacterManager();
			void Add(RemotePlayer* pPlayer);
			RemotePlayer* Remove(RemotePlayer* pPlayer);
			RemotePlayer* Get(unsigned int);
			void Update(float);

		private:

			std::map<unsigned int, RemotePlayer*> mCharacters;
		};
	}
}