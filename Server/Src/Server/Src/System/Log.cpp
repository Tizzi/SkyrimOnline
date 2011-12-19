#include "stdafx.h"
#include "Log.h"

using namespace boost::posix_time;
using namespace boost::gregorian;

namespace Skyrim
{
	namespace System
	{
		Log* Log::mInstance = nullptr;

		Log::Log()
			:mLevel(VERBOSE)
		{
			mLog.open("Server.log",std::ios::trunc);
		}

		Log* Log::GetInstance()
		{
			if(!mInstance)
				mInstance = new Log;
			return mInstance;
		}

		void Log::Print(const std::string& pData)
		{
			if(mLevel <= NONE)
				return;
			mToLog.push(std::make_pair(0,pData));
		}

		void Log::Debug(const std::string& pData)
		{
			if(mLevel < VERBOSE)
				return;

			mToLog.push(std::make_pair(2,pData));
		}

		void Log::Error(const std::string& pData)
		{
			if(mLevel < LOW)
				return;

			mToLog.push(std::make_pair(1,pData));
		}

		void Log::PrintTime()
		{
			ptime now = second_clock::local_time();
			mLog << to_simple_string(now.date()) << " ";
		}

		void Log::SetLevel(Level pLevel)
		{
			mLevel = pLevel;
		}

		void Log::Update()
		{
			std::pair<int, std::string> log;
			while(mToLog.try_pop(log))
			{
				PrintTime();
				switch(log.first)
				{
				case 0:mLog << log.second << std::endl;std::cout << log.second << std::endl;break;
				case 1:mLog << "[ERROR] "<< log.second << std::endl;std::cout << "[ERROR] "<< log.second << std::endl;break;
				case 2:mLog << "[DEBUG] "<< log.second << std::endl;std::cout << "[DEBUG] "<< log.second << std::endl;break;
				}
			}
		}
	}
}