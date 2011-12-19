#pragma once

namespace Skyrim
{
	namespace System
	{
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

			void Update();

		private:

			void PrintTime();

			Log();

			Concurrency::concurrent_queue<std::pair<int, std::string>> mToLog;

			std::ofstream mLog;
			static Log* mInstance;
			Level mLevel;
		};
	}
}