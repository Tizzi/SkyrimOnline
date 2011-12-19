#include "stdafx.h"
#include <Game/StateManager.h>
#include <Common/Log.h>

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		StateManager::StateManager()
			:mState(StateManager::LOGIN)
		{
		}
		//--------------------------------------------------------------------------------
		void StateManager::SetState(StateManager::Enum pState)
		{
			mState = pState;
		}
		//--------------------------------------------------------------------------------
		StateManager::Enum StateManager::GetState()
		{
			return mState;
		}
		//--------------------------------------------------------------------------------
		bool StateManager::IsState(StateManager::Enum pState)
		{
			return mState == pState;
		}
		//--------------------------------------------------------------------------------
	}
}