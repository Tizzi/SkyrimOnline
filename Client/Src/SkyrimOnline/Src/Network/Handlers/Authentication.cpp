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