#include "stdafx.h"
#include <Network/Server.h>
#include <Network/Session.h>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		void Session::HandlePositionAndLook(Packet& pData)
		{
			mPlayer.mPosition.X = pData.Float(0);
			mPlayer.mPosition.Y = pData.Float(1);
			mPlayer.mPosition.Z = pData.Float(2);
			mPlayer.mRotation.X = pData.Float(3);
			mPlayer.mRotation.Y = pData.Float(4);
			mPlayer.mRotation.Z = pData.Float(5);
			mPlayer.mElapsed    = pData.Float(6);

			mWorld->DispatchPlayerMoveAndLook(shared_from_this());
		}
		//---------------------------------------------------------------------
	}
}