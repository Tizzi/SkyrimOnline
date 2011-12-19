#pragma once

namespace Skyrim
{
	namespace Game
	{
		class TimeManager
		{
		public:

			TimeManager();

			void SetHour(float pHour);
			void SetDay(float pDay);
			void SetMonth(float pMonth);

			float GetHour();
			float GetDay();
			float GetMonth();

			void Update(float pElapsed);

		private:

			static int DayPerMonth[12];

			float mHour;
			float mDay;
			float mMonth;
			float mTimeScale;
		};
	}
}