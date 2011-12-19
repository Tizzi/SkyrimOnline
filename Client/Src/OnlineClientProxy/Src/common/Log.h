#pragma once

class Log
{
public:

	enum Level
	{
		NONE,
		LOW,
		VERBOSE
	};

	static Log* GetInstance();
	void Print(const std::string&);
	void Debug(const std::string&);
	void Error(const std::string&);

	void SetLevel(Level pLevel);

private:

	void PrintTime();

	Log();

	std::ofstream mLog;
	static Log* mInstance;
	Level mLevel;
};