/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <System/WorkQueue.h>

namespace Skyrim{
	namespace System
	{
		//---------------------------------------------------------------------
		WorkQueue::WorkQueue(unsigned int pThreadCount)
		{
			for(size_t i = 0; i < pThreadCount; ++i)
			{
				mThreads.push_back(std::make_shared<boost::thread>(boost::bind(&WorkQueue::Run, this)));
			}
		}
		//---------------------------------------------------------------------
		WorkQueue::~WorkQueue()
		{
		}
		//---------------------------------------------------------------------
		void WorkQueue::Run()
		{
			while(1)
			{
				Job* job = nullptr;
				if(mJobs.try_pop(job))
				{
					job->Work();
				}
				else
					boost::thread::yield();
			}
		}
		//---------------------------------------------------------------------
	}
}