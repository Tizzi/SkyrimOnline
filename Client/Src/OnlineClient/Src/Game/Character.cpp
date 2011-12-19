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
	}
}