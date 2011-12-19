#pragma once

namespace SkyrimOnline
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