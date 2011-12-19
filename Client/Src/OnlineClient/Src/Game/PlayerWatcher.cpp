#include "stdafx.h"
#include <Game/PlayerWatcher.h>
#include <Mod.h>
#include <Game/RemotePlayer.h>

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		PlayerWatcher::PlayerWatcher()
			:mPlayer(::Game::GetPlayer()), mSession(nullptr), mMount(false)
		{
		}
		//--------------------------------------------------------------------------------
		void PlayerWatcher::SetSession(Network::Session* pSession)
		{
			mSession = pSession;
		}
		//--------------------------------------------------------------------------------
		void PlayerWatcher::Update(float elapsed)
		{
			mTimer += elapsed;
			mPlayer.SetActor(::Game::GetPlayer());
			if(mSession && mSession->IsOnline())
			{
				// On enter the world
				if(!mSentInfos)
				{
					mSentInfos = true;
					Packet data;
					data.Opcode = CMSG_CHARACTER_INFO;
					data.Push(mPlayer.GetRace());
					data.Push(mPlayer.GetSex());
					data.Push(mPlayer.GetLevel());
					mSession->Write(data);
				}
				// 5 times per sec update pos and rot
				if(mTimer >= 0.2)
				{
					Packet data;
					data.Opcode = CMSG_POSITION_LOOK;
					data.Push(mPlayer.GetPosX());
					data.Push(mPlayer.GetPosY());
					data.Push(mPlayer.GetPosZ());
					data.Push(mPlayer.GetRotX());
					data.Push(mPlayer.GetRotY());
					data.Push(mPlayer.GetRotZ());
					data.Push(mTimer);
					mSession->Write(data);

					// if mount or unmount
					if(mMount != mPlayer.IsRidding())
					{
						mMount = mPlayer.IsRidding();
						if(mMount)
						{
							// Associate mount to player
							Packet mount;
							mount.Opcode = CMSG_MOUNT_SPAWN;
							mount.Int(0x0010982B);
							mSession->Write(data);
						}
						else
						{
							// Dettach mount
							Packet mount;
							mount.Opcode = CMSG_MOUNT_REMOVE;
							mount.Int(0);
							mSession->Write(data);
						}
					}

					mTimer = 0;
				}
			}
		}
		//--------------------------------------------------------------------------------
		bool PlayerWatcher::IsDead()
		{
			return mPlayer.IsDead();
		}
		//--------------------------------------------------------------------------------
	}
}