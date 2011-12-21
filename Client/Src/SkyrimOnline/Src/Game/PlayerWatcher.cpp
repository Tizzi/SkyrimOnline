/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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
							mount.Push((unsigned int)mPlayer.GetMountID());
							mSession->Write(mount);
						}
						else
						{
							// Dettach mount
							Packet mount;
							mount.Opcode = CMSG_MOUNT_REMOVE;
							mSession->Write(mount);
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