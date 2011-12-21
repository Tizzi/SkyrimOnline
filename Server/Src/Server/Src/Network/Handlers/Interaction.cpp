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
#include <Network/Server.h>
#include <Game/Player.h>
#include <Game/Mount.h>
#include <fstream>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		void Session::HandleChatMessage(Packet& pData)
		{
			if((clock() - mTimeSinceLastMessage)/CLOCKS_PER_SEC >= 5)
			{
				std::string str = pData.String(0);
				if(str == "/total")
				{
					Packet packet;
					packet.Opcode = SMSG_CHAT;
					std::ostringstream os;
					os << "Total players online : " << mServer->Count();
					packet.Push(os.str());
					Write(packet);
				}
				else if(str == "/count")
				{
					Packet packet;
					packet.Opcode = SMSG_CHAT;
					std::ostringstream os;
					os << "Players online on this shard : " << mWorld->Count();
					packet.Push(os.str());
					Write(packet);
				}
				else
				{
					std::ostringstream os;
					if(mAccount._level == 10)
					{
						os << "#00FFFF";
					}
					os << "[" << mAccount._nicename << "]#FFFFFF says : " << pData.String(0);

					Packet packet;
					packet.Opcode = SMSG_CHAT;
					packet.Push(os.str());
					mWorld->DispatchToAll(packet);

					mTimeSinceLastMessage = clock();
				}
			}
			else
			{
				Packet lol;
				lol.Opcode = SMSG_CHAT;
				lol.Push(std::string("SpamControl is unhappy ! Wait 5 seconds between each message !"));
				Write(lol);
			}
		}
		//---------------------------------------------------------------------
		void Session::HandlePlayerEvent(Session::pointer pPlayer)
		{
			auto itor = std::find(mInRange.begin(), mInRange.end(), pPlayer);
			if(itor == mInRange.end())
			{
				if(GetDistance(pPlayer) < 10000)
				{
					SendSpawnPlayer(pPlayer);
					mInRange.push_back(pPlayer);
				}
			}
			else
			{
				if(GetDistance(pPlayer) > 15000)
				{
					SendRemove(pPlayer);
					mInRange.erase(itor);
				}
				else
				{
					SendMoveAndLook(pPlayer);
				}
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleMount(Packet& pData)
		{
			if(pData.Int(0) != 0)
			{
				GetPlayer().SetMount(pData.Int(0));
				Packet packet;
				packet.Opcode = SMSG_PLAYER_MOUNT_SPAWN;
				packet.Push(GetId());
				packet.Push(pData.Int(0));
				DispatchInRange(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleUnmount(Packet& pData)
		{
			GetPlayer().SetMount(0);
			Packet packet;
			packet.Opcode = SMSG_PLAYER_MOUNT_REMOVE;
			packet.Push(GetId());
			DispatchInRange(packet);
		}
		//---------------------------------------------------------------------
		float Session::GetDistance(Session::pointer pPlayer)
		{
			return pPlayer->GetPlayer().mPosition.Distance(mPlayer.mPosition);
		}
		//---------------------------------------------------------------------
	}
}