#pragma once

#include <DAO/DAO.h>

namespace Skyrim{
	namespace System
	{
		class DBWorkQueue
		{
		public:

			enum Type{
				SAVE,
				LOAD
			};

			DBWorkQueue(unsigned int pThreadCount);
			~DBWorkQueue();

			void Run(std::shared_ptr<SimpleDB::Database> pDatabase);

			void Push(std::shared_ptr<DAO::IDAO> pObject);

		private:
			Concurrency::concurrent_queue<std::shared_ptr<DAO::IDAO>> mJobs;
			std::list<std::shared_ptr<boost::thread>> mThreads;
		};
	}
}