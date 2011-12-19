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
				packet.Push(pPlayer->GetPlayer().GetMount()->GetSkyrimId());
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