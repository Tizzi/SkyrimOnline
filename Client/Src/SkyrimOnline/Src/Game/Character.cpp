/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include "Character.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		Character::Character(CActor* pActor)
			:mActor(pActor)
		{
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosX()
		{
			return ObjectReference::GetPositionX((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosY()
		{
			return ObjectReference::GetPositionY((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetPosZ()
		{
			return ObjectReference::GetPositionZ((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotX()
		{
			return ObjectReference::GetAngleX((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotY()
		{
			return ObjectReference::GetAngleY((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		float Character::GetRotZ()
		{
			return ObjectReference::GetAngleZ((TESObjectREFR*)mActor);
		}
		//--------------------------------------------------------------------------------
		unsigned int Character::GetLevel()
		{
			return Actor::GetLevel(mActor);
		}
		//--------------------------------------------------------------------------------
		unsigned int Character::GetRace()
		{
			return Form::GetFormID((TESForm*)Actor::GetRace(mActor));
		}
		//--------------------------------------------------------------------------------
		bool Character::IsDead()
		{
			return Actor::IsDead(mActor);
		}
		//--------------------------------------------------------------------------------
		unsigned int Character::GetSex()
		{
			return ActorBase::GetSex((TESNPC*)mActor);
		}
		//--------------------------------------------------------------------------------
		CActor* Character::actor()
		{
			return mActor;
		}
		//--------------------------------------------------------------------------------
		void Character::SetPos(float x, float y, float z)
		{
			ObjectReference::SetPosition((TESObjectREFR*)mActor,x,y,z);
		}
		//--------------------------------------------------------------------------------
		void Character::SetRot(float x, float y, float z)
		{
			ObjectReference::SetAngle((TESObjectREFR*)mActor,x,y,z);
		}
		//--------------------------------------------------------------------------------
		void Character::SetActor(CActor* pActor)
		{
			mActor = pActor;
		}
		//--------------------------------------------------------------------------------
		bool Character::IsRidding()
		{
			return Obscript::IsRidingHorse((TESObjectREFR*)mActor) == 1.f;
		}
		//--------------------------------------------------------------------------------
		unsigned int Character::GetMountID()
		{
			if (IsRidding())
			{
				CActor * lMount = ::Game::GetPlayersLastRiddenHorse();
				if(lMount)
				{
					return Form::GetFormID(ObjectReference::GetBaseObject((TESObjectREFR*)lMount));
				}
			}

			return 0;
		}
		//--------------------------------------------------------------------------------
	}
}