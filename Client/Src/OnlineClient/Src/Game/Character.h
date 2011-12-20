#pragma once

namespace SkyrimOnline
{
	namespace Game
	{
		class Character
		{
		public:

			Character(CActor* pActor);

			float GetPosX();
			float GetPosY();
			float GetPosZ();

			float GetRotX();
			float GetRotY();
			float GetRotZ();

			void SetPos(float x, float y, float z);
			void SetRot(float x, float y, float z);

			bool IsRidding();
			unsigned int GetMountID();

			unsigned int GetSex();
			unsigned int GetRace();
			unsigned int GetLevel();

			bool IsDead();

			CActor* actor();
			void SetActor(CActor* pActor);

		private:

			CActor* mActor;
		};
	}
}