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