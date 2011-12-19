// !!!!!! NOTE !!!!!!
// This WILL be deprecated as soon as it is implemented server side
// Do not use

#pragma once

#include "Wave.h"
#include <Engine/InputManager.h>

namespace SkyrimOnline
{
	namespace Game
	{
		class WaveManager
		{
		public:

			WaveManager();
			Wave GetWave(unsigned int id);
			unsigned int GetCount();
			void Run();

			void OnPress(BYTE code);
			void OnRelease(BYTE code);

			void Clear();

		private:

			std::vector<Wave> mWaves;
			BYTE mKeyResume;
			BYTE mKeyStart;
			BYTE mKeyStop;
			unsigned int mCount;
			Wave mCurrentWave;
			bool mCanInstanciate;
			bool mStarted;
			long mTimeRemaining;
		};
	}
}