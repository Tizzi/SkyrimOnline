#include "stdafx.h"
#include "Wave.h"
#include <Overlay/Interface.h>
#include <Overlay/Chat.h>
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void GetRelXyFromRef(TESObjectREFR *ref, float dist, float addangle, float *x, float *y)
		{
			float rzrot = ObjectReference::GetAngleZ(ref);
			rzrot = (float)(rzrot * 3.14 / 180) + addangle;
			if (x) *x = dist*sin(rzrot);
			if (y) *y = dist*cos(rzrot);
		}
		//--------------------------------------------------------------------------------
		CActor* AddEnemy(unsigned int id)
		{
			auto ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(id), 1, false, false);
			ObjectReference::MoveTo((TESObjectREFR *)ref, (TESObjectREFR *)::Game::GetPlayer(), (rand() % 1000) - 500, (rand() % 1000) - 500, 0, false);
			Actor::SetRelationshipRank((CActor*)::Game::GetPlayer(), (CActor*)ref, -4);
			return (CActor*)ref;
		}
		//--------------------------------------------------------------------------------
		Wave::Wave()
			:mInstanciated(false), mTotal(0)
		{}
		//--------------------------------------------------------------------------------
		Wave::~Wave()
		{
			Kill();
		}
		//--------------------------------------------------------------------------------
		void Wave::Add(const Tier& pTier)
		{
			mTiers.push_back(pTier);
			mTotal += pTier.mCount;
		}
		//--------------------------------------------------------------------------------
		bool Wave::Complete()
		{
			return mRefs.size() == 0 && mInstanciated;
		}
		//--------------------------------------------------------------------------------
		void Wave::Instanciate()
		{
			try
			{
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] Get ready spawning "+MyGUI::utility::toString(mTotal)+" units !","#FFFF66");
			}
			catch (...)
			{
			}
			for(auto itor = mTiers.begin(); itor != mTiers.end(); ++itor)
			{
				for(unsigned int i = 0; i < itor->mCount; ++i)
				{
					mRefs.push_back(AddEnemy(itor->mId));
					Wait(200);
				}
			}
			for(auto itor = mRefs.begin(); itor != mRefs.end(); ++itor)
			{
				for(auto it = mRefs.begin(); it != mRefs.end(); ++it)
					Actor::SetRelationshipRank(*it, *itor, 4);
			}
			mInstanciated = true;
		}
		//--------------------------------------------------------------------------------
		void Wave::Update()
		{
			for(auto itor = mRefs.begin(); itor != mRefs.end(); ++itor)
			{
				if(Actor::IsDead(*itor))
				{
					itor = mRefs.erase(itor);
					try
					{
						SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[Arena] You killed "+MyGUI::utility::toString(mTotal-mRefs.size())+" out of "+MyGUI::utility::toString(mTotal)+" units","#FFFF66");
					}
					catch (...)
					{
					}
				}
			}
		}
		//--------------------------------------------------------------------------------
		void Wave::Kill()
		{
			for(auto itor = mRefs.begin(); itor != mRefs.end(); ++itor)
			{
				Actor::Kill(*itor, *itor);
			}
			mRefs.clear();
		}
		//--------------------------------------------------------------------------------
	}
}