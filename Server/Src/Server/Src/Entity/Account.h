#pragma once

namespace Skyrim{
	namespace Entity
	{
		class Account
		{
		public:

			Account()
				:_banned(false),_id(0),_level(0)
			{
			}

			bool _banned;
			std::string _pass;
			std::string _user;
			std::string _nicename;
			uint32_t _level;
			uint32_t _id;
		};
	}
}