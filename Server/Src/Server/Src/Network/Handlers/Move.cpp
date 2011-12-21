/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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