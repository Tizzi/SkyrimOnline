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