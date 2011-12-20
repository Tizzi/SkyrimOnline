#include "stdafx.h"
#include "RemotePlayer.h"
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		RemotePlayer::RemotePlayer(unsigned int pId, unsigned int pRace, int pSex)
			:mID(pId), mMe(nullptr), mInit(false), mMount(nullptr)
		{
			unsigned int actorId = ID_TESNPC::BretonMalePreset10;
			if(pSex == -1)
			{
				switch(pRace)
				{
				case Skyrim::Race::Altmer: actorId = ID_TESNPC::HighElfMalePreset10; break;
				case Skyrim::Race::Bosmer: actorId = ID_TESNPC::WoodElfMalePreset10; break;
				case Skyrim::Race::Argorian: actorId = ID_TESNPC::ArgonianMalePreset10; break;
				case Skyrim::Race::Dunmer: actorId = ID_TESNPC::DarkElfMalePreset10; break;
				case Skyrim::Race::Imperial: actorId = ID_TESNPC::ImperialMalePreset10; break;
				case Skyrim::Race::Khajiit: actorId = ID_TESNPC::KhajiitMalePreset10; break;
				case Skyrim::Race::Nord: actorId = ID_TESNPC::NordMalePreset10; break;
				case Skyrim::Race::Orc: actorId = ID_TESNPC::OrcMalePreset10; break;
				case Skyrim::Race::Redguard: actorId = ID_TESNPC::RedguardMalePreset10; break;
				}
			}
			else
			{
				actorId = ID_TESNPC::BretonFemalePreset10;
				switch(pRace)
				{
				case Skyrim::Race::Altmer: actorId = ID_TESNPC::HighElfFemalePreset10; break;
				case Skyrim::Race::Bosmer: actorId = ID_TESNPC::WoodElfFemalePreset10; break;
				case Skyrim::Race::Argorian: actorId = ID_TESNPC::ArgonianFemalePreset10; break;
				case Skyrim::Race::Dunmer: actorId = ID_TESNPC::DarkElfFemalePreset10; break;
				case Skyrim::Race::Imperial: actorId = ID_TESNPC::ImperialFemalePreset10; break;
				case Skyrim::Race::Khajiit: actorId = ID_TESNPC::KhajiitFemalePreset10; break;
				case Skyrim::Race::Nord: actorId = ID_TESNPC::NordFemalePreset10; break;
				case Skyrim::Race::Orc: actorId = ID_TESNPC::OrcFemalePreset10; break;
				case Skyrim::Race::Redguard: actorId = ID_TESNPC::RedguardFemalePreset10; break;
				}
			}
			mMe = new Character((CActor*)ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(actorId), 1, true, false));
			Actor::EnableAI(mMe->actor(), false);
			Mod::GetInstance().GetAssetManager().Add((TESObjectREFR*)mMe->actor());
		}
		//--------------------------------------------------------------------------------
		RemotePlayer::~RemotePlayer()
		{
			SetMount(0);
			Mod::GetInstance().GetAssetManager().Remove((TESObjectREFR*)mMe->actor());
			ObjectReference::Delete((TESObjectREFR*)mMe->actor());
			delete mMe;
		}
		//--------------------------------------------------------------------------------
		Character* RemotePlayer::character()
		{
			return mMe;
		}
		//--------------------------------------------------------------------------------
		unsigned int RemotePlayer::id()
		{
			return mID;
		}
		//--------------------------------------------------------------------------------
		void RemotePlayer::SetPosition(float x, float y, float z)
		{
			mMe->SetPos(x,y,z);
			if(mMount)
				mMount->SetPos(x,y,z);
		}
		//--------------------------------------------------------------------------------
		void RemotePlayer::SetRotation(float x, float y, float z)
		{
			mMe->SetRot(x,y,z);
			if(mMount)
				mMount->SetRot(x,y,z);
		}
		//--------------------------------------------------------------------------------
		void RemotePlayer::InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float time)
		{
			mPrevious = mNext;

			if(!mInit) time = 0;

			mNext.posX = posX;
			mNext.posY = posY;
			mNext.posZ = posZ;
			mNext.rotX = rotX;
			mNext.rotY = rotY;
			mNext.rotZ = rotZ;
			mNext.elapsed = time;

			if(!mInit)
			{
				mPrevious = mNext;
				mInit = true;
				SetPosition(mPrevious.posX,mPrevious.posY ,mPrevious.posZ);
				SetRotation(mPrevious.rotX,mPrevious.rotY ,mPrevious.rotZ);
			}
			else
			{
				float a = mNext.posX - mPrevious.posX;
				float b = mNext.posY - mPrevious.posY;
				float c = mNext.posZ - mPrevious.posZ;
				float speed = sqrt(a*a + b*b + c*c)/mNext.elapsed;
				ObjectReference::TranslateTo((TESObjectREFR*)mMe->actor(),mNext.posX, mNext.posY, mNext.posZ, mNext.rotX, mNext.rotY, mNext.rotZ,speed, 200);
				if(mMount)
					ObjectReference::TranslateTo((TESObjectREFR*)mMount->actor(),mNext.posX, mNext.posY, mNext.posZ, mNext.rotX, mNext.rotY, mNext.rotZ,speed, 200);
			}

			ObjectReference::PlayAnimation((TESObjectREFR*)mMe->actor(), "Walk");
		}
		//--------------------------------------------------------------------------------
		void RemotePlayer::Update(float elapsed)
		{
		}
		//--------------------------------------------------------------------------------
		void RemotePlayer::SetMount(unsigned int pMount)
		{
			if(mMount)
			{
				Mod::GetInstance().GetAssetManager().Remove((TESObjectREFR*)mMount->actor());
				ObjectReference::Delete((TESObjectREFR*)mMount->actor());
				delete mMount;
				mMount = nullptr;
			}
			if(pMount != 0)
			{
				mMount = new Character((CActor*)ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(pMount), 1, true, false));
				mMount->SetPos(mMe->GetPosX(), mMe->GetPosY(), mMe->GetPosZ());
				mMount->SetRot(mMe->GetRotX(), mMe->GetRotY(), mMe->GetRotZ());

				Actor::EnableAI(mMount->actor(), false);
				
				ObjectReference::TetherToHorse((TESObjectREFR*)mMe->actor(), (TESObjectREFR*)mMount->actor());
				
				Mod::GetInstance().GetAssetManager().Add((TESObjectREFR*)mMount->actor());
			}
		}
		//--------------------------------------------------------------------------------
	}
}