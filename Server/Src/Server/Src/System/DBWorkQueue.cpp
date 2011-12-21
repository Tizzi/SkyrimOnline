/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <System/DBWorkQueue.h>

namespace Skyrim{
	namespace System
	{
		//---------------------------------------------------------------------
		DBWorkQueue::DBWorkQueue(unsigned int pThreadCount)
		{
			try
			{
				for(size_t i = 0; i < pThreadCount; ++i)
				{
					mThreads.push_back(std::make_shared<boost::thread>(boost::bind(&DBWorkQueue::Run, this, std::make_shared<SimpleDB::Database>("Wordpress"))));
				}
			}
			catch(std::exception& e)
			{
				Skyrim::System::Log::GetInstance()->Error(e.what());
			}
		}
		//---------------------------------------------------------------------
		DBWorkQueue::~DBWorkQueue()
		{
		}
		//---------------------------------------------------------------------
		void DBWorkQueue::Push(std::shared_ptr<DAO::IDAO> pObject)
		{
			mJobs.push(pObject);
		}
		//---------------------------------------------------------------------
		void DBWorkQueue::Run(std::shared_ptr<SimpleDB::Database> pDatabase)
		{
			while(1)
			{
				std::shared_ptr<DAO::IDAO> task;
				if(mJobs.try_pop(task))
				{
					switch(task->type())
					{
					case DAO::IDAO::LOAD:
						task->Load(*pDatabase);break;
					case DAO::IDAO::SAVE:
						task->Save(*pDatabase);break;
					}
				}
				else
					boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}
		}
		//---------------------------------------------------------------------
	}
}