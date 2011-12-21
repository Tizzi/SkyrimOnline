/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "CharacterManager.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		CharacterManager::CharacterManager()
		{
		}
		//--------------------------------------------------------------------------------
		CharacterManager::~CharacterManager()
		{
			Log::GetInstance()->Debug("CharacterManager::~CharacterManager()");
			for(auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
			{
				delete itor->second;
			}
			mCharacters.clear();
		}
		//--------------------------------------------------------------------------------
		void CharacterManager::Add(RemotePlayer* pPlayer)
		{
			if(mCharacters.find(pPlayer->id()) == mCharacters.end())
				mCharacters[pPlayer->id()] = pPlayer;
		}
		//--------------------------------------------------------------------------------
		RemotePlayer* CharacterManager::Remove(RemotePlayer* pPlayer)
		{
			auto itor = mCharacters.find(pPlayer->id());
			if(itor != mCharacters.end())
				mCharacters.erase(itor);
			return pPlayer;
		}
		//--------------------------------------------------------------------------------
		RemotePlayer* CharacterManager::Get(unsigned int pPlayer)
		{
			return mCharacters[pPlayer];
		}
		//--------------------------------------------------------------------------------
		void CharacterManager::Update(float elapsed)
		{
			for(auto itor = mCharacters.begin(); itor != mCharacters.end(); ++itor)
			{
				itor->second->Update(elapsed);
			}
		}
		//--------------------------------------------------------------------------------
	}
}