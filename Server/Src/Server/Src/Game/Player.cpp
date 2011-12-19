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