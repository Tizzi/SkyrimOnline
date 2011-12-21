/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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