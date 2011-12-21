/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <System/EventEmitter.h>

using namespace std;

namespace Skyrim{
	//---------------------------------------------------------------------
	inline const string stringSQLSafe(const string &in, const bool escapePercentage = false)
	{
		string retval;

		for (string::const_iterator it = in.begin(); it != in.end(); it++) {
			if (*it == '\"') {
				retval += "\\\"";
			} else if (*it == '\'') {
				retval += "\\'";
			} else if (*it == '\\') {
				retval += "\\\\";
			} else if (escapePercentage && (*it == '%') ) {
				retval += "\\%";
			} else {
				retval += *it;
			}
		}

		return retval;
	}

	namespace DAO
	{
		class IDAO : public System::EventEmitter
		{
		public:

			IDAO(){}
			virtual ~IDAO(){}

			virtual void Load(SimpleDB::Database& pDatabase) = 0;
			virtual void Save(SimpleDB::Database& pDatabase) = 0;

			struct LoadEvent : System::Event
			{
				System::Event::Type type(){return System::Event::DATAOBJECT_LOAD;}
			};

			struct FailLoadEvent : System::Event
			{
				System::Event::Type type(){return System::Event::DATAOBJECT_LOAD_FAIL;}
			};

			struct SaveEvent : System::Event
			{
				System::Event::Type type(){return System::Event::DATAOBJECT_SAVE;}
			};

			enum Type
			{
				LOAD,SAVE
			};

			virtual IDAO::Type type() = 0;

			unsigned int userData;

		protected:

			void NotifyLoad()
			{
				auto event = std::dynamic_pointer_cast<System::Event>(std::make_shared<LoadEvent>());
				event->userData = userData;
				Dispatch(event);
			}

			void NotifyLoadFail()
			{
				auto event = std::dynamic_pointer_cast<System::Event>(std::make_shared<FailLoadEvent>());
				event->userData = userData;
				Dispatch(event);
			}

			void NotifySave()
			{
				auto event = std::dynamic_pointer_cast<System::Event>(std::make_shared<SaveEvent>());
				event->userData = userData;
				Dispatch(event);
			}
		};

		template <class T>
		class DAO : public IDAO
		{
			T& mEntity;
			IDAO::Type mType;
		public:

			DAO(T& pEntity, IDAO::Type pType)
				:mEntity(pEntity),mType(pType)
			{
			}

			virtual ~DAO(){}

			IDAO::Type type()
			{
				return mType;
			}

			void Load(SimpleDB::Database& pDatabase);
			void Save(SimpleDB::Database& pDatabase);
		};

		template <class T, class U>
		class DAOk : public DAO<T>
		{
			std::shared_ptr<U> mKeep;
		public:
			DAOk(T& pEntity, IDAO::Type pType, std::shared_ptr<U> pKeep)
				:DAO(pEntity,pType),mKeep(pKeep)
			{}

			virtual ~DAOk(){}
		};

		template <class T>
		std::shared_ptr<IDAO> Load(T& pObject)
		{
			return std::shared_ptr<IDAO>(new DAO<T>(pObject, IDAO::LOAD));
		}

		template <class T>
		std::shared_ptr<IDAO> Save(T& pObject)
		{
			return std::shared_ptr<IDAO>(new DAO<T>(pObject, IDAO::SAVE));
		}

		template <class T, class U>
		std::shared_ptr<IDAO> Load(T& pObject, std::shared_ptr<U> pKeep)
		{
			return std::shared_ptr<IDAO>(new DAOk<T,U>(pObject, IDAO::LOAD, pKeep));
		}

		template <class T, class U>
		std::shared_ptr<IDAO> Save(T& pObject, std::shared_ptr<U> pKeep)
		{
			return std::shared_ptr<IDAO>(new DAOk<T,U>(pObject, IDAO::SAVE, pKeep));
		}
	}
}