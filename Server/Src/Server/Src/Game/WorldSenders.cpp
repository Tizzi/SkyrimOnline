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