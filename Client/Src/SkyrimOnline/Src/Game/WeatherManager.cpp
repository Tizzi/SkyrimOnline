/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "WeatherManager.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WeatherManager::WeatherManager()
			:mWeather(0)
		{
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::SetWeather(unsigned int pWeather)
		{
			mWeather = pWeather;
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Update(float pElapsed)
		{
			if(Form::GetFormID((TESForm*)Weather::GetCurrentWeather()) != mWeather && mWeather != 0)
			{
				Weather::ForceActive((TESWeather*)::Game::GetFormById(mWeather), true);
			}
		}
		//--------------------------------------------------------------------------------
	}
}