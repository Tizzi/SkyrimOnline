/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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