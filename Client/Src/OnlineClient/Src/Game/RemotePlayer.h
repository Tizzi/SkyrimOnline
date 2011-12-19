#pragma once

#include "Character.h"

namespace SkyrimOnline
{
	namespace Game
	{
		class __declspec(dllexport) RemotePlayer
		{
		public:

			RemotePlayer(unsigned int pId, unsigned int pRace, int pSex);
			~RemotePlayer();

			void Update(float elapsed);
			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void InterpolateTo(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float time);
			void SetMount(unsigned int pMount);

			Character* character();
			unsigned int id();

		private:

			struct InterpolationPoint
			{
				float posX, posY, posZ;
				float rotX, rotY, rotZ;
				float elapsed;
			};

			InterpolationPoint mPrevious, mNext;
			bool mInit;
			unsigned int mID;
			Character* mMe;
			Character* mMount;
		};
	}
}