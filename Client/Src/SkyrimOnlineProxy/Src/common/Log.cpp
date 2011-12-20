#include "stdafx.h"
#include "Log.h"

Log* Log::mInstance = nullptr;

using namespace boost::posix_time;
using namespace boost::gregorian;

Log::Log()
	:mLevel(VERBOSE)
{
	mLog.open("SkyrimOnline.log",std::ios::trunc);
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

	PrintTime();
	mLog << pData << std::endl;
}

void Log::Debug(const std::string& pData)
{
	if(mLevel < VERBOSE)
		return;

	PrintTime();
	mLog << "[DEBUG] " << pData << std::endl;
}

void Log::Error(const std::string& pData)
{
	if(mLevel < LOW)
		return;

	PrintTime();
	mLog << "[ERROR] "<< pData << std::endl;
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