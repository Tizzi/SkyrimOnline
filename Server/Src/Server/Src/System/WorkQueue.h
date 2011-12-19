#pragma once

#include <System/Job.h>

namespace Skyrim{
	namespace System
	{
		class WorkQueue
		{
		public:

			WorkQueue(unsigned int pThreadCount);
			~WorkQueue();

			void Run();

		private:
			Concurrency::concurrent_queue<Job*> mJobs;
			std::list<std::shared_ptr<boost::thread>> mThreads;
		};
	}
}