#include "stdafx.h"
#include <Network/Server.h>

int main()
{
	try
	{
		auto server = std::make_shared<Skyrim::Network::Server>(8558);
		server->Start();
	}
	catch (std::exception& e)
	{
		Skyrim::System::Log::GetInstance()->Error(e.what());
	}

	system("pause");
	return 0;
}