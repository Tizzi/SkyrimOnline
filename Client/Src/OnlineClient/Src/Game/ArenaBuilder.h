#pragma once

namespace SkyrimOnline
{
	namespace Game
	{
		class ArenaBuilder
		{
		public:

			static const unsigned int Wall;
			static const unsigned int Pillar;
			static const unsigned int Bench;
			static const unsigned int Statue;
			static const unsigned int Fence;
			static const unsigned int Tower;
			static const unsigned int Arch;

			ArenaBuilder();
			~ArenaBuilder();

		private:

			float mX,mY,mZ;
			std::list<TESObjectREFR*> mObjects;
		};
	}
}