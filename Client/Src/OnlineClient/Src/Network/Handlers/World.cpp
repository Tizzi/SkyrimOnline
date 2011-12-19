#include "stdafx.h"
#include <Network/Session.h>
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <Overlay/ShardList.h>
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Network
	{
		//--------------------------------------------------------------------------------
		void Session::HandleTimeSync(Packet& data)
		{
			Mod::GetInstance().GetTimeManager().SetHour(data.Float(0));
			Mod::GetInstance().GetTimeManager().SetDay(data.Float(1));
			Mod::GetInstance().GetTimeManager().SetMonth(data.Float(2));
		}
		//--------------------------------------------------------------------------------
		void Session::HandleWeatherSync(Packet& data)
		{
			Mod::GetInstance().GetWeatherManager().SetWeather(data.Int(0));
		}
		//--------------------------------------------------------------------------------
	}
}