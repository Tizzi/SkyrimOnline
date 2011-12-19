#pragma once

namespace SkyrimOnline
{
	namespace Game
	{
		class StateManager
		{
		public:

			enum Enum
			{
				LOGIN,
				SHARD_LIST,
				IN_GAME,
				LOADING
			};

			StateManager();
			Enum GetState();
			void SetState(Enum pState);
			bool IsState(Enum pState);

		private:

			Enum mState;
		};
	}
}