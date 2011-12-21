/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "World.h"
#include <Network/Packet.h>

namespace Skyrim{
	namespace Game
	{
		//---------------------------------------------------------------------
		void World::SendTimeSync(Network::Session::pointer pPlayer)
		{
			Network::Packet packet;
			packet.Opcode = SMSG_TIME_SYNC;
			packet.Push(mTimeManager.GetHour());
			packet.Push(mTimeManager.GetDay());
			packet.Push(mTimeManager.GetMonth());
			pPlayer->Write(packet);
		}
		//---------------------------------------------------------------------
		void World::SendWeatherSync(Network::Session::pointer pPlayer)
		{
			Network::Packet packet;
			packet.Opcode = SMSG_WEATHER_SYNC;
			packet.Push(mWeatherManager.GetWeather());
			pPlayer->Write(packet);
		}
		//---------------------------------------------------------------------
	}
}