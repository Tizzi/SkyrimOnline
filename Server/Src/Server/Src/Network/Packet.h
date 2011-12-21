/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

enum Opcode
{
	CMSG_AUTHENTICATION,
	CMSG_POSITION_LOOK,
	CMSG_CHARACTER_INFO,
	SMSG_PLAYER_COUNT,
	SMSG_PLAYER_SPAWN,
	SMSG_PLAYER_MOVE_LOOK,
	SMSG_PLAYER_REMOVE,
	SMSG_NEW_PLAYER,
	CMSG_CHAT,
	SMSG_CHAT,
	CMSG_MAGIC,
	SMSG_TIME_SYNC,
	SMSG_SHARD_LIST,
	CMSG_SHARD_PICK,
	SMSG_SHARD_HANDSHAKE,
	SMSG_WEATHER_SYNC,
	SMSG_PLAYER_MOUNT_SPAWN,
	SMSG_PLAYER_MOUNT_REMOVE,
	CMSG_MOUNT_SPAWN,
	CMSG_MOUNT_REMOVE
};

namespace Skyrim
{
	namespace Network
	{
		class Packet
		{
		public:

			friend class boost::serialization::access;

			//--------------------------------------------------------------------//
			/// @brief Serialize the class
			/// @param ar The archive to use
			//--------------------------------------------------------------------//
			template<class Archive>
			void serialize(Archive& ar, const unsigned int)
			{
				ar & Opcode;
				ar & mIntData;
				ar & mFloatData;
				ar & mString;
			}

			//--------------------------------------------------------------------//
			/// @brief Returns an int value
			/// @param n The value's index
			/// @return The value
			//--------------------------------------------------------------------//
			unsigned int					Int(int n){return mIntData.at(n);}

			//--------------------------------------------------------------------//
			/// @brief Returns a float value
			/// @param n The value's index
			/// @return The value
			//--------------------------------------------------------------------//
			float					Float(int n){return mFloatData.at(n);}

			//--------------------------------------------------------------------//
			/// @brief Returns a wstring value
			/// @param n The value's index
			/// @return The value
			//--------------------------------------------------------------------//
			std::string			String(int n){return mString.at(n);}

			//--------------------------------------------------------------------//
			/// @brief Add a value to the packet
			/// @param n The value to push
			//--------------------------------------------------------------------//
			void					Push(unsigned int n){mIntData.push_back(n);}

			//--------------------------------------------------------------------//
			/// @brief Add a value to the packet
			/// @param n The value to push
			//--------------------------------------------------------------------//
			void					Push(float n){mFloatData.push_back(n);}

			//--------------------------------------------------------------------//
			/// @brief Add a value to the packet
			/// @param n The value to push
			//--------------------------------------------------------------------//
			void					Push(const std::string& n){mString.push_back(n);}

			unsigned short				Opcode;

		protected:

			std::vector<unsigned int>	mIntData;
			std::vector<float>			mFloatData;
			std::vector<std::string>	mString;
		};
	}
}