#include "stdafx.h"
#include "Session.h"
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Network
	{
		//--------------------------------------------------------------------------------
		std::unordered_map<unsigned int, Session::CallBack> Session::mHandlers;
		//--------------------------------------------------------------------------------
		void Session::Init()
		{
			mHandlers[SMSG_PLAYER_COUNT] = &Session::HandlePlayerCount;
			mHandlers[SMSG_SHARD_LIST] = &Session::HandleShardList;
			mHandlers[SMSG_SHARD_HANDSHAKE] = &Session::HandleShardHandShake;
			mHandlers[SMSG_PLAYER_SPAWN] = &Session::HandlePlayerSpawn;
			mHandlers[SMSG_PLAYER_MOVE_LOOK] = &Session::HandlePlayerMoveAndLook;
			mHandlers[SMSG_PLAYER_REMOVE] = &Session::HandlePlayerRemove;
			mHandlers[SMSG_NEW_PLAYER] = &Session::HandleNewPlayer;
			mHandlers[SMSG_CHAT] = &Session::HandleChatMessage;
			mHandlers[SMSG_TIME_SYNC] = &Session::HandleTimeSync;
			mHandlers[SMSG_WEATHER_SYNC] = &Session::HandleWeatherSync;
			mHandlers[SMSG_PLAYER_MOUNT_SPAWN] = &Session::HandleMount;
			mHandlers[SMSG_PLAYER_MOUNT_REMOVE] = &Session::HandleUnmount;
		}
		//--------------------------------------------------------------------------------
		Session::Session()
			:mConnected(false),mIoService(new boost::asio::io_service)
		{
			mWork = new boost::asio::io_service::work(*mIoService);
			socket_ = new tcp::socket(*mIoService);
			resolver_ = new tcp::resolver(*mIoService);
		}
		//--------------------------------------------------------------------------------
		Session::~Session()
		{
			try{
				Log::GetInstance()->Debug("Session::~Session()");
				delete mWork;
				mThread->join();
				delete mThread;
				delete socket_;
				delete resolver_;
			}
			catch(...)
			{
				Log::GetInstance()->Debug("Session::~Session() error");
			}
			Log::GetInstance()->Debug("alright !");
		}
		//--------------------------------------------------------------------------------
		void Session::Start()
		{
			try{
				tcp::resolver::query query("skyrim-online.com", "8558");

				handle_resolve(resolver_->resolve(query));
			}
			catch(std::exception& e)
			{
			}
		}
		//--------------------------------------------------------------------------------
		void Session::Write(const Packet& msg)
		{
			socket_->get_io_service().post(boost::bind(&Session::do_write,this, msg));
		}
		//--------------------------------------------------------------------------------
		void Session::close()
		{
			try{
				mConnected = false;
				socket_->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				socket_->close();
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Debug(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		bool Session::IsOnline()
		{
			return mConnected;
		}
		//--------------------------------------------------------------------------------
		void Session::Run()
		{
			Packet data;
			while(mPackets.try_pop(data))
			{
				try{
					(this->*mHandlers.at(data.Opcode))(data);
				}
				catch(const std::out_of_range&)
				{
				}
			}
		}
		//--------------------------------------------------------------------------------
		void Session::handle_resolve(tcp::resolver::iterator endpoint_iterator)
		{
			boost::system::error_code e;
			socket_->connect(*endpoint_iterator, e);
			handle_connect(e);
		}
		//--------------------------------------------------------------------------------
		void Session::handle_connect(const boost::system::error_code& error)
		{
			try
			{
				if (!error)
				{
					boost::asio::ip::tcp::no_delay option(true);
					socket_->set_option(option);
					async_read();

					Packet packet;
					packet.Opcode = CMSG_MAGIC;
					packet.Push((Skyrim::Version << 2) * 3);
					Write(packet);

					mConnected = true;

					if(mThread == nullptr)
						mThread = new boost::thread(boost::bind(&boost::asio::io_service::run, mIoService));
				}
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::handle_read(const boost::system::error_code& error)
		{
			if (!error)
			{
				mPackets.push(mReceivingPacket);
				async_read();
			}
			else
			{
				close();
				Mod::GetInstance().OnConnectionLost();
			}
		}
		//--------------------------------------------------------------------------------
		void Session::do_write(Packet msg)
		{
			bool write_in_progress = !mToSend.empty();
			mToSend.push_back(msg);
			if (!write_in_progress)
			{
				async_write(mToSend.front());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::handle_write(const boost::system::error_code& error)
		{
			--count_;
			if (!error)
			{
				mToSend.pop_front();
				if (!mToSend.empty())
				{
					async_write(mToSend.front());
				}
			}
			else
			{
				Log::GetInstance()->Debug("handle_write failed");
			}
		}
		//--------------------------------------------------------------------------------
		void Session::do_close()
		{
			try{
				socket_->close();
			}
			catch(...)
			{
			}
		}
		//--------------------------------------------------------------------------------
	}
}