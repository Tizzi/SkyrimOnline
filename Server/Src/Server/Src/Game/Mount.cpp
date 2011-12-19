#include "stdafx.h"
#include <Game/Mount.h>

namespace Skyrim
{
	namespace Game
	{
		//---------------------------------------------------------------------
		Mount::Mount(unsigned int pSkyrimID)
			:mSkyrimID(pSkyrimID)
		{
		}
		//---------------------------------------------------------------------
		unsigned int Mount::GetSkyrimId()
		{
			return mSkyrimID;
		}
		//---------------------------------------------------------------------
	}
}