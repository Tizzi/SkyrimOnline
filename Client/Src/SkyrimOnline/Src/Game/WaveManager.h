/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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