/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Game/Player.h>
#include <Game/Mount.h>

namespace Skyrim
{
	namespace Game
	{
		//---------------------------------------------------------------------
		Player::Player()
			:mMount(nullptr)
		{
		}
		//---------------------------------------------------------------------
		Player::~Player()
		{
			delete mMount;
		}
		//---------------------------------------------------------------------
		unsigned int Player::level()
		{
			return mLevel;
		}
		//---------------------------------------------------------------------
		unsigned int Player::race()
		{
			return mRace;
		}
		//---------------------------------------------------------------------
		unsigned int Player::sex()
		{
			return mSex;
		}
		//---------------------------------------------------------------------
		Mount* Player::GetMount()
		{
			return mMount;
		}
		//---------------------------------------------------------------------
		bool Player::HasMount()
		{
			return mMount != nullptr;
		}
		//---------------------------------------------------------------------
		void Player::SetMount(unsigned int pMountID)
		{
			if(HasMount())
			{
				if(mMount->GetSkyrimId() == pMountID)
					return;
				delete mMount; mMount = nullptr;
			}
			mMount = new Mount(pMountID);
		}
		//---------------------------------------------------------------------
	}
}