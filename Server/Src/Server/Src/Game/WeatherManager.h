#pragma once

namespace Skyrim
{
	namespace Game
	{
		class WeatherManager
		{
		public:

			WeatherManager();

			void Update(float pElapsed);

			unsigned int GetWeather();

		private:

			struct Weather
			{
				int id;
				char *name;
			};
			static Weather Weathers[];
			unsigned int mWeather;
		};
	}
}