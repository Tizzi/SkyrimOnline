#pragma once

namespace SkyrimOnline
{
	namespace Game
	{
		class Wave
		{
		public:

			class Tier
			{
			public:
				Tier(unsigned int id, unsigned int count)
					:mId(id),mCount(count)
				{
				}
				unsigned int mId, mCount;
			};

			Wave();
			~Wave();

			void Add(const Tier&);
			void Instanciate();
			bool Complete();
			void Update();
			void Kill();

		private:

			std::list<Tier> mTiers;
			std::list<CActor*> mRefs;
			bool mInstanciated;
			unsigned int mTotal;
		};
	}
}