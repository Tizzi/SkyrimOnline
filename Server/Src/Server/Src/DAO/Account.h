/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <Entity/Account.h>
#include <DAO/DAO.h>

namespace Skyrim{
	namespace DAO
	{
		template <>
		inline void DAO<Entity::Account>::Load(SimpleDB::Database& pDatabase)
		{
			try
			{
				std::ostringstream oss;
				oss << "SELECT ID, user_pass, user_login, user_nicename, meta_value FROM wp_users INNER JOIN wp_usermeta ON ID=user_id WHERE meta_key='wp_user_level' AND user_login='" << stringSQLSafe(mEntity._user)
					<< "' AND user_pass=MD5('" << stringSQLSafe(mEntity._pass) << "')";

				SimpleDB::Query query(pDatabase);
				SimpleDB::StringColumn pass(33), user(61), nicename(61);
				SimpleDB::IntColumn id,level;
				SimpleDB::Column * cols[] = {&id,&pass,&user,&nicename,&level};
				query.bind(cols,5);
				query.execute(oss.str());

				if(query.fetchRow())
				{
					mEntity._pass = pass.value();
					mEntity._user = user.value();
					mEntity._id = id.value();
					mEntity._level = level.value();
					mEntity._nicename = nicename.value();

					/*std::ostringstream charS;
					charS << "SELECT server_id FROM other_personnages WHERE account='" << mEntity._id << "'";

					SimpleDB::Query query(pDatabase);
					SimpleDB::IntColumn serverId;
					SimpleDB::Column * cols[] = {&serverId};
					query.bind(cols,1);
					query.execute(charS.str());
					while(query.fetchRow())
					{
						Entity::Character character;
						character._serverId = serverId.value();

						mEntity._characters.push_back(character);
					}*/
				}
				else
					throw std::runtime_error("Account not found");
			}
			catch(std::exception& e)
			{
				System::Log::GetInstance()->Error(e.what());
			}

			NotifyLoad();
		}

		template <>
		inline void DAO<Entity::Account>::Save(SimpleDB::Database& pDatabase)
		{
			try
			{
				/*std::ostringstream oss;
				oss << "UPDATE realm_accounts SET ticket='" << mEntity._ticket << "' WHERE guid='" << mEntity._id << "'";
				pDatabase.voidQuery(oss.str());*/
			}
			catch(std::exception& e)
			{
				Skyrim::System::Log::GetInstance()->Error(e.what());
			}

			NotifySave();
		}
	}
}