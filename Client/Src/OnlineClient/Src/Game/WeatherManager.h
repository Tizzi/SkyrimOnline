#pragma once

namespace SkyrimOnline
{
	namespace Game
	{
		class WeatherManager
		{
		public:

			WeatherManager();

			void SetWeather(unsigned int pWeather);

			void Update(float pElapsed);

		private:

			unsigned int mWeather;
		};
	}
}