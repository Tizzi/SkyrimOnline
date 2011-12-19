#include "stdafx.h"
#include <Network/Session.h>
#include <Network/Server.h>
#include <DAO/Account.h>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		void Session::HandleAuth(Packet& pData)
		{
			if(mAccount._id == 0)
			{
				mAccount._user = pData.String(0);
				mAccount._pass = pData.String(1);

				auto dao = DAO::Load(mAccount);
				dao->Add(shared_from_this());
				dao->userData = LOAD_USER;
				mServer->GetDatabaseWorkQueue()->Push(dao);
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleUserLoad()
		{
			if(mAccount._id != 0)
			{
				mAuth = true;
				GetServer().SendShardList(shared_from_this());
			}
			else
			{
				Close();
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleShardPick(Packet& pData)
		{
			if(mAccount._id != 0)
				GetServer().MoveToWorld(pData.String(0), shared_from_this());
		}
		//---------------------------------------------------------------------
	}
}