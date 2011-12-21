/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#include "stdafx.h"
#include <Network/Session.h>
#include <Network/Server.h>
#include <fstream>

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		std::unordered_map<unsigned int, Session::CallBack> Session::mHandlers;
		std::unordered_map<unsigned int, Session::CallBack> Session::mAuthHandlers;
		std::unordered_map<unsigned int, Session::QueryCallback> Session::mQueryHandlers;
		//---------------------------------------------------------------------
		Session::Session(boost::asio::io_service& pIoService, Server* pServer)
			:mSocket(pIoService), mServer(pServer), mAuth(false), mTimeSinceLastMessage(0), mWorld(nullptr)
		{
		}
		//---------------------------------------------------------------------
		Session::~Session()
		{
		}
		//---------------------------------------------------------------------
		void Session::Close()
		{
			mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_type::shutdown_both);
			mSocket.close();
		}
		//---------------------------------------------------------------------
		void Session::Start()
		{
			std::ostringstream os;
			os << "Started listening to : " << mSocket.remote_endpoint().address().to_string() << " Online : " << mServer->Count() << ", Peak : " << mServer->Peak();
			System::Log::GetInstance()->Debug(os.str());

			boost::asio::ip::tcp::no_delay option(true);
			mSocket.set_option(option);

			async_read(mReceivingPacket,
				boost::bind(&Session::HandleRead, this,
				boost::asio::placeholders::error,
				shared_from_this()));
		}
		//---------------------------------------------------------------------
		void Session::Write(Packet& pData)
		{
			mSocket.get_io_service().post(boost::bind(&Session::DoWrite, this, pData, shared_from_this()));
		}
		//---------------------------------------------------------------------
		void Session::DoWrite(Packet pData, std::shared_ptr<Session> pSession)
		{
			bool write_in_progress = !mToSend.empty();
			mToSend.push_back(pData);
			if (!write_in_progress)
			{
				async_write(mToSend.front(),
					boost::bind(&Session::HandleWrite, this, boost::asio::placeholders::error, shared_from_this()));
			}
		}
		//---------------------------------------------------------------------
		Server& Session::GetServer()
		{
			return *mServer;
		}
		//---------------------------------------------------------------------
		void Session::Run()
		{
			System::Event::pointer e;
			while(mEvents.try_pop(e))
			{
				try{
					(this->*mQueryHandlers.at(e->userData))();
				}
				catch(...)
				{
				}
			}

			Packet data;
			while(mPackets.try_pop(data))
			{
				try{
					if(mAuth && mWorld)
						(this->*mHandlers.at(data.Opcode))(data);
					else if(mAuth)
						(this->*mAuthHandlers.at(data.Opcode))(data);
					else if(data.Opcode == CMSG_MAGIC && data.Int(0) == ((Version << 2) * 3))
						mAuth = true;
					else
						mSocket.close();
				}
				catch(...)
				{
					std::ostringstream os;
					os << "Ran into an unknown packet Opcode : " << std::hex << data.Opcode;
					System::Log::GetInstance()->Error(os.str());
				}
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleRead(const boost::system::error_code& pError, Session::pointer pMe)
		{
			if(!pError)
			{
				mPackets.push(mReceivingPacket);

				async_read(mReceivingPacket,
					boost::bind(&Session::HandleRead, this,
					boost::asio::placeholders::error,
					shared_from_this()));
			}
			else
			{
				//std::cout << pError.message() << std::endl;
				mServer->Remove(shared_from_this());
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleWrite(const boost::system::error_code& pError, Session::pointer pMe)
		{
			if(!pError)
			{
				mToSend.pop_front();
				if (!mToSend.empty())
				{
					async_write(mToSend.front(),
						boost::bind(&Session::HandleWrite, this, boost::asio::placeholders::error, shared_from_this()));
				}
			}
			else
			{
			}
		}
		//---------------------------------------------------------------------
		boost::asio::ip::tcp::socket& Session::GetSocket()
		{
			return mSocket;
		}
		//---------------------------------------------------------------------
		void Session::Setup()
		{
			mHandlers[CMSG_POSITION_LOOK] = &Session::HandlePositionAndLook;
			mHandlers[CMSG_CHARACTER_INFO] = &Session::HandleCharacterInfo;
			mHandlers[CMSG_CHAT] = &Session::HandleChatMessage;
			mHandlers[CMSG_MOUNT_SPAWN] = &Session::HandleMount;
			mHandlers[CMSG_MOUNT_REMOVE] = &Session::HandleUnmount;

			mAuthHandlers[CMSG_SHARD_PICK] = &Session::HandleShardPick;
			mAuthHandlers[CMSG_AUTHENTICATION] = &Session::HandleAuth;

			mQueryHandlers[LOAD_USER] = &Session::HandleUserLoad;
		}
		//---------------------------------------------------------------------
		Game::Player& Session::GetPlayer()
		{
			return mPlayer;
		}
		//---------------------------------------------------------------------
		Game::World* Session::GetWorld()
		{
			return mWorld;
		}
		//---------------------------------------------------------------------
		void Session::SetWorld(Game::World* pWorld)
		{
			mWorld = pWorld;
		}
		//---------------------------------------------------------------------
		void Session::Remove(Session::pointer pPlayer)
		{
			auto itor = std::find(mInRange.begin(), mInRange.end(), pPlayer);
			if(itor != mInRange.end())
			{
				SendRemove(pPlayer);
				mInRange.erase(itor);
			}
		}
		//---------------------------------------------------------------------
		void Session::DispatchInRange(Packet& data)
		{
			auto end = mInRange.end();
			for(auto itor = mInRange.begin(); itor != end; ++itor)
			{
				(*itor)->Write(data);
			}
		}
		//---------------------------------------------------------------------
		unsigned int Session::GetId()
		{
			return mAccount._id;
		}
		//---------------------------------------------------------------------
	}
}