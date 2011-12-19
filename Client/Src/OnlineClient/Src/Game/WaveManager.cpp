#include "stdafx.h"
#include "WaveManager.h"
#include <Overlay/Chat.h>
#include <Mod.h>
#include <Overlay/Interface.h>

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WaveManager::WaveManager()
		{
			Log::GetInstance()->Debug("WaveManager::WaveManager() - b #deprecated");
			mWaves.resize(4);
			mWaves[0].Add(Wave::Tier(Skyrim::Wolf,4));
			mWaves[1].Add(Wave::Tier(Skyrim::Wolf,4));
			mWaves[1].Add(Wave::Tier(Skyrim::Bandit,2));
			mWaves[2].Add(Wave::Tier(Skyrim::SabreCat,1));
			mWaves[2].Add(Wave::Tier(Skyrim::Bandit,4));
			mWaves[3].Add(Wave::Tier(Skyrim::SabreCat,4));
			mWaves[3].Add(Wave::Tier(Skyrim::BanditChief,3));

			// Controls
			mKeyResume = DIK_NUMPAD7;
			mKeyStart = DIK_NUMPAD8;
			mKeyStop = DIK_NUMPAD9;

			mCount = 0;
			mCanInstanciate = true;
			mStarted = false;
			mTimeRemaining = 0;

			Log::GetInstance()->Debug("WaveManager::WaveManager() - e #deprecated");
		}
		//--------------------------------------------------------------------------------
		Wave WaveManager::GetWave(unsigned int id)
		{
			if(id < mWaves.size())
			{
				return mWaves[id];
			}
			return mWaves[mWaves.size() - 1];
		}
		//--------------------------------------------------------------------------------
		unsigned int WaveManager::GetCount()
		{
			return mWaves.size();
		}
		//--------------------------------------------------------------------------------
		void WaveManager::Clear()
		{
			mStarted = false;
			mCurrentWave.Kill();
		}
		//--------------------------------------------------------------------------------
		void WaveManager::OnPress(BYTE code)
		{
		}
		//--------------------------------------------------------------------------------
		void WaveManager::OnRelease(BYTE code)
		{
			if(code == mKeyResume && !mStarted)
			{
				try
				{
					SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] Resuming progress !","#FFFF66");
				}
				catch (...)
				{
				}
				std::ifstream saved("./Data/Online/User/Arena.db");
				if(saved.is_open())
				{
					saved >> mCount;
				}
				mCurrentWave = GetWave(mCount);
				mCurrentWave.Instanciate();
				mCanInstanciate = false;
				mStarted = true;
			}
			else if(code == mKeyStart && !mStarted)
			{
				try
				{
					SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] Starting from first wave !","#FFFF66");
				}
				catch (...)
				{
				}
				mCount = 0;
				mCurrentWave = GetWave(mCount);
				mCurrentWave.Instanciate();
				mCanInstanciate = false;
				mStarted = true;
			}

			if(mStarted)
			{
				if(code == mKeyStop)
				{
					std::ofstream saved("./Data/Online/User/Arena.db", std::ios::trunc);
					if(saved.is_open())
					{
						saved << mCount;
					}
					Clear();
					try
					{
						SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] shutting down.","#FFFF66");
					}
					catch (...)
					{
					}
				}
				if(code == mKeyResume && mCanInstanciate)
				{
					mTimeRemaining = 0;
				}
			}
		}
		//--------------------------------------------------------------------------------
		void WaveManager::Run()
		{
			if(mStarted)
			{
				if(mCanInstanciate)
				{
					if(clock() - mTimeRemaining >= 15 * 1000)
					{
						++mCount;
						mCurrentWave = GetWave(mCount);
						mCurrentWave.Instanciate();
						mCanInstanciate = false;
					}
				}
				else if(mCurrentWave.Complete())
				{
					try
					{
						SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] Congratulations ! You completed wave " + MyGUI::utility::toString(mCount+1), "#00FFFF");
						SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] Next wave in 15 seconds","#FFFF66");
					}
					catch (...)
					{
					}

					mCanInstanciate = true;
					mTimeRemaining = clock();
				}
				else
					mCurrentWave.Update();
			}
		}
		//--------------------------------------------------------------------------------
	}
}