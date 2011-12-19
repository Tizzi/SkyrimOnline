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