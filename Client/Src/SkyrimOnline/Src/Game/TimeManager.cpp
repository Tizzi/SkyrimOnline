/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "TimeManager.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		int TimeManager::DayPerMonth[12] =
		{
			31,28,31,30,31,30,31,31,30,31,30,31
		};
		//--------------------------------------------------------------------------------
		TimeManager::TimeManager()
			:mDay(0),mMonth(0),mHour(0),mTimeScale(24.f/6.f)
		{
			SetGlobalSetting(ID_TESGlobal::TimeScale, 0);
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetDay(float pDay)
		{
			mDay = pDay;
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetMonth(float pMonth)
		{
			mMonth = pMonth;
		}
		//--------------------------------------------------------------------------------
		void TimeManager::SetHour(float pHour)
		{
			mHour = pHour;
		}
		//--------------------------------------------------------------------------------
		void TimeManager::Update(float pElapsed)
		{
			mHour += (pElapsed/3600.f) * mTimeScale;
			if(mHour > 24.f)
			{
				mHour -= 24.f;
				mDay += 1;
				if(mDay > DayPerMonth[(int)mMonth])
				{
					mMonth++;
					mDay = 1;
				}
				if(mMonth > 12)
					mMonth = 1;
			}

			SetGlobalSetting(ID_TESGlobal::GameHour, mHour);
			SetGlobalSetting(ID_TESGlobal::GameDay,  mDay);
			SetGlobalSetting(ID_TESGlobal::GameMonth, mMonth);
		}
		//--------------------------------------------------------------------------------
	}
}