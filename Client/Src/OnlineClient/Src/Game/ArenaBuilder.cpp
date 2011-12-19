#include "stdafx.h"
#include "ArenaBuilder.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		const unsigned int ArenaBuilder::Wall = 0x78aa1;
		const unsigned int ArenaBuilder::Pillar = 0xf0f2b;
		const unsigned int ArenaBuilder::Bench = 0xf0f2b;
		const unsigned int ArenaBuilder::Statue = 0xd068d;
		const unsigned int ArenaBuilder::Fence = 0xcd8b5;
		const unsigned int ArenaBuilder::Tower = 0x4B77C;
		const unsigned int ArenaBuilder::Arch = 0x37cc5;
		//--------------------------------------------------------------------------------
		ArenaBuilder::ArenaBuilder()
			:mY(10521.6),mX(-19166.3),mZ(-7266)
		{
			// Walls
			//Left
			auto ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX,mY,mZ);
			ObjectReference::SetAngle(ref,0,0,180.f);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX,mY+830,mZ);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX,mY+830*2,mZ);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			//Back
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(),:: Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830/2,mY-(830/2),mZ);
			ObjectReference::SetAngle(ref,0,0,90.f);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*1.5,mY-(830/2),mZ);
			ObjectReference::SetAngle(ref,0,0,270.f);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*2.5,mY-(830/2),mZ);
			ObjectReference::SetAngle(ref,0,0,270.f);
			mObjects.push_back(ref);
			//Right
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*3,mY,mZ);
			ObjectReference::SetAngle(ref,0,0,180.f);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*3,mY+830,mZ);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*3,mY+830*2,mZ);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			// Front
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830/2,mY+(830*2.5)-50,mZ);
			ObjectReference::SetAngle(ref,0,0,270.0f);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Wall), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*2.5,mY+(830*2.5)-50,mZ);
			ObjectReference::SetAngle(ref,0,0,90.0f);
			mObjects.push_back(ref);

			//Towers
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Tower), 1, true, false);
			ObjectReference::SetPosition(ref,mX-350,mY+50,mZ+130);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Tower), 1, true, false);
			ObjectReference::SetPosition(ref,mX-430 - 830*2,mY+50,mZ+40);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);

			// Arch & statues
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Statue), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830-80,mY+(830*2.5)+200,mZ-270);
			ObjectReference::SetAngle(ref,0,0,180);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Statue), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*2 + 80,mY+(830*2.5)+200,mZ-270);
			ObjectReference::SetAngle(ref,0,0,180);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Arch), 1, true, false);
			ObjectReference::SetPosition(ref,mX-830*1.5-120 + 100,mY+(830*2.5)-50,mZ);
			ObjectReference::SetAngle(ref,0,0,90.0f);
			mObjects.push_back(ref);

			// Pillars
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Pillar), 1, true, false);
			ObjectReference::SetPosition(ref,mX- 800,mY+700,mZ-250);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Pillar), 1, true, false);
			ObjectReference::SetPosition(ref,mX- 1600,mY+700,mZ-250);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Pillar), 1, true, false);
			ObjectReference::SetPosition(ref,mX-800,mY+1400,mZ-250);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
			ref = ObjectReference::PlaceAtMe((TESObjectREFR*)::Game::GetPlayer(), ::Game::GetFormById(Pillar), 1, true, false);
			ObjectReference::SetPosition(ref,mX - 1600,mY+1400,mZ-250);
			ObjectReference::SetAngle(ref,0,0,0);
			mObjects.push_back(ref);
		}
		//--------------------------------------------------------------------------------
		ArenaBuilder::~ArenaBuilder()
		{
			for(auto itor = mObjects.begin(); itor != mObjects.end(); ++itor)
			{
				ObjectReference::Delete(*itor);
			}
		}
		//--------------------------------------------------------------------------------
	}
}