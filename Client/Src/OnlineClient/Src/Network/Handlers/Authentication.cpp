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
		void Session::HandleShardList(Packet& data)
		{
			for(unsigned int i = 0; i < data.Int(0); ++i)
			{
				Mod::GetInstance().GetInterface().GetShardList()->Log(data.String(i));
			}
			Mod::GetInstance().EnterState(Game::StateManager::SHARD_LIST);
		}
		//--------------------------------------------------------------------------------
		void Session::HandleShardHandShake(Packet& data)
		{
			if(data.Int(0) == 1)
			{
				Mod::GetInstance().EnterState(Game::StateManager::IN_GAME);
			}
		}
		//--------------------------------------------------------------------------------
	}
}