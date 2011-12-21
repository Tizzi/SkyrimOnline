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

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WeatherManager::Weather WeatherManager::Weathers[] = {
			{ID_TESWeather::DefaultWeather, "DefaultWeather"},
			{ID_TESWeather::SovngardeDark, "SovngardeDark"},
			{ID_TESWeather::RiftenOvercastFog, "RiftenOvercastFog"},
			{ID_TESWeather::EditorCloudPreview, "EditorCloudPreview"},
			{ID_TESWeather::SkyrimClear_A, "SkyrimClear_A"},
			{ID_TESWeather::SkyrimCloudy_A, "SkyrimCloudy_A"},
			/*ID_TESWeather::SkyrimClearSN_A,
			ID_TESWeather::SkyrimCloudySN_A,
			ID_TESWeather::SkyrimClearTU_A,
			ID_TESWeather::SkyrimCloudyTU_A,
			ID_TESWeather::SkyrimClearFF_A,
			ID_TESWeather::SkyrimCloudyFF_A,
			ID_TESWeather::SkyrimClearRE_A,
			ID_TESWeather::SkyrimCloudyRE_A,
			ID_TESWeather::SkyrimClearCO_A,
			ID_TESWeather::SkyrimCloudyCO_A,
			ID_TESWeather::SkyrimClearMA_A,
			ID_TESWeather::SkyrimCloudyMA_A,
			ID_TESWeather::SkyrimClearVT_A,
			ID_TESWeather::SkyrimCloudyVT_A,
			ID_TESWeather::FXWthrInvertWindowsWinterhold,*/ // 20
			{ID_TESWeather::SovngardeClear, "SovngardeClear"},
			{ID_TESWeather::FXSkyrimStormBlowingGrass, "FXSkyrimStormBlowingGrass"},
			{ID_TESWeather::SkyrimCloudyVT, "SkyrimCloudyVT"},
			{ID_TESWeather::SkyrimFogVT, "SkyrimFogVT"},
			{ID_TESWeather::SkyrimOvercastRainVT, "SkyrimOvercastRainVT"}, // 25
			/*ID_TESWeather::SkyrimClearVT,
			ID_TESWeather::SkyrimCloudySN,
			ID_TESWeather::SkyrimClearSN,*/   // 28
			{ID_TESWeather::SkyrimCloudyTU, "SkyrimCloudyTU"},
			{ID_TESWeather::SkyrimOvercastRainTU, "SkyrimOvercastRainTU"}, // 30
			{ID_TESWeather::SkyrimStormRainTU, "SkyrimStormRainTU"},
			{ID_TESWeather::SkyrimClearTU, "SkyrimClearTU"},
			//ID_TESWeather::SkyrimCloudyFF,
			{ID_TESWeather::SkyrimFogFF, "SkyrimFogFF"},
			/*ID_TESWeather::SkyrimOvercastRainFF,
			ID_TESWeather::SkyrimStormRainFF,*/
			{ID_TESWeather::SkyrimClearFF, "SkyrimClearFF"},
			/*ID_TESWeather::SkyrimCloudyRE,
			ID_TESWeather::SkyrimFogRE,
			ID_TESWeather::SkyrimOvercastRainRE, // 40
			ID_TESWeather::SkyrimClearRE,*/
			/*ID_TESWeather::SkyrimCloudyCO,
			ID_TESWeather::SkyrimFogCO,
			ID_TESWeather::SkyrimClearCO,
			ID_TESWeather::SkyrimCloudyMA,
			ID_TESWeather::SkyrimFogMA,
			ID_TESWeather::SkyrimOvercastRainMA,
			ID_TESWeather::SkyrimClearMA,*/
			{ID_TESWeather::KarthspireRedoubtFog, "KarthspireRedoubtFog"},
			{ID_TESWeather::SkyrimDA02Weather, "SkyrimDA02Weather"}, // 50
			{ID_TESWeather::SolitudeBluePalaceFog, "SolitudeBluePalaceFog"},
			{ID_TESWeather::SolitudeBluePalaceFogNMARE, "SolitudeBluePalaceFogNMARE"},
			{ID_TESWeather::SolitudeBluePalaceFogFEAR, "SolitudeBluePalaceFogFEAR"},
			{ID_TESWeather::SolitudeBluePalaceFogARENA, "SolitudeBluePalaceFogARENA"},
			{ID_TESWeather::BloatedMansGrottoFog, "BloatedMansGrottoFog"},// 55
			{ID_TESWeather::SkuldafnCloudy, "SkuldafnCloudy"},
			{ID_TESWeather::SkyrimMQ206weather, "SkyrimMQ206weather"},
			//ID_TESWeather::FXWthrInvertLightMarkarth,
			//ID_TESWeather::FXWthrInvertWindowsWindhelm2,
			//ID_TESWeather::HelgenAttackWeather, // 60
			//ID_TESWeather::FXWthrInvertLightsSolitude,
			//ID_TESWeather::FXWthrInvertLightsWhiterun,
			//ID_TESWeather::FXWthrInvertWindowsWhiterun,
			{ID_TESWeather::FXMagicStormRain, "FXMagicStormRain"},
			{ID_TESWeather::SkyrimOvercastWar, "SkyrimOvercastWar"},
			{ID_TESWeather::SkyrimStormSnow, "SkyrimStormSnow"},
			{ID_TESWeather::SkyrimStormRain, "SkyrimStormRain"},
			{ID_TESWeather::SkyrimOvercastRain, "SkyrimOvercastRain"},
			{ID_TESWeather::SkyrimFog, "SkyrimFog"},
			//ID_TESWeather::FXWthrSunlightWhite,
			{ID_TESWeather::FXWthrSunlight, "FXWthrSunlight"},
			{ID_TESWeather::BlackreachWeather, "BlackreachWeather"},
			//ID_TESWeather::FXWthrInvertWindowsWindhelm,
			//ID_TESWeather::WorldMapWeather,
			{ID_TESWeather::SovngardeFog, "SovngardeFog"},
			//ID_TESWeather::FXWthrInvertDayNighWarm,
			//ID_TESWeather::FXWthrCaveBluePaleLight,
			{ID_TESWeather::FXWthrCaveBlueSkylight, "FXWthrCaveBlueSkylight"},
			//ID_TESWeather::FXWthrInvertDayNight,
			{ID_TESWeather::SkyrimOvercastSnow, "SkyrimOvercastSnow"},
			//ID_TESWeather::TESTCloudyRain,
			//ID_TESWeather::SkyrimCloudy,
			{ID_TESWeather::SkyrimClear, "SkyrimClear"}
		};

		//--------------------------------------------------------------------------------
		WeatherManager::WeatherManager()
			:mWeather(37)
		{
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Update(float pElapsed)
		{
		}
		//--------------------------------------------------------------------------------
		unsigned int WeatherManager::GetWeather()
		{
			return Weathers[mWeather].id;
		}
		//--------------------------------------------------------------------------------
	}
}