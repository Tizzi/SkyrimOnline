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
#include <Game/Mount.h>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		void Session::HandleCharacterInfo(Packet& pData)
		{
			mPlayer.mRace = pData.Int(0);
			mPlayer.mSex = pData.Int(1);
			mPlayer.mLevel = pData.Int(2);
		}
		//---------------------------------------------------------------------
		void Session::SendSpawnPlayer(Session::pointer pPlayer)
		{
			Packet data;
			data.Opcode = SMSG_PLAYER_SPAWN;

			data.Push(pPlayer->GetId());
			data.Push(pPlayer->GetPlayer().race());
			data.Push(pPlayer->GetPlayer().sex());
			data.Push(pPlayer->GetPlayer().level());
			Write(data);

			SendMount(pPlayer);
		}
		//---------------------------------------------------------------------
		void Session::SendMount(Session::pointer pPlayer)
		{
			if(pPlayer->GetPlayer().HasMount())
			{
				Packet packet;
				packet.Opcode = SMSG_PLAYER_MOUNT_SPAWN;
				packet.Push(pPlayer->GetId());
				packet.Push(pPlayer->GetPlayer().GetMount()->GetSkyrimId());
				Write(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::SendUnmount(Session::pointer pPlayer)
		{
			if(pPlayer->GetPlayer().HasMount())
			{
				Packet packet;
				packet.Opcode = SMSG_PLAYER_MOUNT_REMOVE;
				packet.Push(pPlayer->GetId());
				Write(packet);
			}
		}
		//---------------------------------------------------------------------
		void Session::SendMoveAndLook(Session::pointer pPlayer)
		{
			Packet data;
			data.Opcode = SMSG_PLAYER_MOVE_LOOK;
			data.Push(pPlayer->GetId());
			data.Push(pPlayer->GetPlayer().mPosition.X);
			data.Push(pPlayer->GetPlayer().mPosition.Y);
			data.Push(pPlayer->GetPlayer().mPosition.Z);
			data.Push(pPlayer->GetPlayer().mRotation.X);
			data.Push(pPlayer->GetPlayer().mRotation.Y);
			data.Push(pPlayer->GetPlayer().mRotation.Z);
			data.Push(pPlayer->GetPlayer().mElapsed);

			Write(data);
		}
		//---------------------------------------------------------------------
		void Session::SendRemove		(Session::pointer pPlayer)
		{
			Packet data;
			data.Opcode = SMSG_PLAYER_REMOVE;

			data.Push(pPlayer->GetId());

			Write(data);
		}
		//---------------------------------------------------------------------
	}
}