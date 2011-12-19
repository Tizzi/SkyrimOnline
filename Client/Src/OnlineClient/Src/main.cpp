#include "stdafx.h"
#include <Mod.h>

__declspec(dllexport) void main()
{
	//std::ostringstream os;
	//for(int i = 0; i < 6; ++i)
	//	os << Actor::Item
	//Log::GetInstance()->Debug(os.str());

	srand((unsigned int)time(NULL));
	PrintNote("To play Skyrim Online, press F3");

	bool onlineMod = false;
	while(!SkyrimOnline::Mod::Exists())
	{
		if(GetKeyPressed(VK_F3))
		{
			onlineMod = true;
			break;
		}
		Wait(0);
	}

	if(onlineMod || SkyrimOnline::Mod::Exists())
		SkyrimOnline::Mod::GetInstance().Run();
}