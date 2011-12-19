#pragma once

#include <System/EventListener.h>
#include <Entity/Account.h>
#include <Network/Packet.h>
#include <Game/Player.h>

namespace Skyrim
{
	namespace Game
	{
		class World;
	}
	namespace Network
	{
		class Server;

		typedef std::deque<Packet> PacketQueue;

		class Session
			:	public std::enable_shared_from_this<Session>,
				public System::EventListener
		{
		public:

			typedef std::shared_ptr<Session> pointer;

			enum Queries
			{
				LOAD_USER = 0
			};

			Session(boost::asio::io_service& pIoService, Server* pServer);
			~Session();

			void Start();
			void Run();
			void Write();
			void Write(Packet& pData);
			void Close();

			boost::asio::ip::tcp::socket& GetSocket();

			Server& GetServer();
			Game::Player& GetPlayer();
			Game::World* GetWorld();

			void SetWorld(Game::World* pWorld);

			static void Setup();

			void SendSpawnPlayer(Session::pointer pOther);
			void SendMoveAndLook(Session::pointer pOther);
			void SendRemove		(Session::pointer pOther);
			void SendMount		(Session::pointer pOther);
			void SendUnmount	(Session::pointer pOther);

			void HandlePlayerEvent(pointer pPlayer);
			float GetDistance(pointer pPlayer);

			void Remove(pointer pPlayer);

			unsigned int GetId();

		protected:

			/// Asynchronously write a data structure to the socket.
			template <typename T, typename Handler>
			void async_write(const T& t, Handler handler)
			{
				// Serialize the data first so we know how large it is.
				std::ostringstream archive_stream;
				boost::archive::text_oarchive archive(archive_stream);
				archive << t;
				outbound_data_ = archive_stream.str();
				unsigned int size = (unsigned int)outbound_data_.size();
				// Format the header.
				outbound_header_.clear();
				outbound_header_.append((char*)&size,4);

				if (outbound_header_.size() != header_length)
				{
					// Something went wrong, inform the caller.
					boost::system::error_code error(boost::asio::error::invalid_argument);
					mSocket.get_io_service().post(boost::bind(handler, error));
					return;
				}

				// Write the serialized data to the socket. We use "gather-write" to send
				// both the header and the data in a single write operation.
				std::vector<boost::asio::const_buffer> buffers;
				buffers.push_back(boost::asio::buffer(outbound_header_));
				buffers.push_back(boost::asio::buffer(outbound_data_));
				boost::asio::async_write(mSocket, buffers, handler);
			}

			/// Asynchronously read a data structure from the socket.
			template <typename T, typename Handler>
			void async_read(T& t, Handler handler)
			{
				// Issue a read operation to read exactly the number of bytes in a header.
				void (Session::*f)(
					const boost::system::error_code&,
					T&, boost::tuple<Handler>)
					= &Session::handle_read_header<T, Handler>;
				boost::asio::async_read(mSocket, boost::asio::buffer(inbound_header_),
					boost::bind(f,
					this, boost::asio::placeholders::error, boost::ref(t),
					boost::make_tuple(handler)));
			}

			/// Handle a completed read of a message header. The handler is passed using
			/// a tuple since boost::bind seems to have trouble binding a function object
			/// created using boost::bind as a parameter.
			template <typename T, typename Handler>
			void handle_read_header(const boost::system::error_code& e,
				T& t, boost::tuple<Handler> handler)
			{
				if (e)
				{
					boost::get<0>(handler)(e);
				}
				else
				{
					std::size_t inbound_data_size = *(unsigned int*)inbound_header_;
					if (inbound_data_size > 1 << 16)
					{
						// Header doesn't seem to be valid. Inform the caller.
						boost::system::error_code error(boost::asio::error::invalid_argument);
						boost::get<0>(handler)(error);
						return;
					}

					// Start an asynchronous call to receive the data.
					inbound_data_.resize(inbound_data_size);
					void (Session::*f)(
						const boost::system::error_code&,
						T&, boost::tuple<Handler>)
						= &Session::handle_read_data<T, Handler>;
					boost::asio::async_read(mSocket, boost::asio::buffer(inbound_data_),
						boost::bind(f, this,
						boost::asio::placeholders::error, boost::ref(t), handler));
				}
			}

			/// Handle a completed read of message data.
			template <typename T, typename Handler>
			void handle_read_data(const boost::system::error_code& e,
				T& t, boost::tuple<Handler> handler)
			{
				if (e)
				{
					boost::get<0>(handler)(e);
				}
				else
				{
					// Extract the data structure from the data just received.
					try
					{
						std::string archive_data(&inbound_data_[0], inbound_data_.size());
						std::istringstream archive_stream(archive_data);
						boost::archive::text_iarchive archive(archive_stream);
						archive >> t;
					}
					catch (...)
					{
						// Unable to decode data.
						boost::system::error_code error(boost::asio::error::invalid_argument);
						boost::get<0>(handler)(error);
						return;
					}

					// Inform caller that data has been received ok.
					boost::get<0>(handler)(e);
				}
			}

			void HandleRead	(const boost::system::error_code& pError,pointer pMe);
			void HandleWrite(const boost::system::error_code& pError, pointer pMe);
			void DoWrite(Packet data, pointer pSession);
			void DispatchInRange(Packet& data);

			/// Handlers
			void HandleAuth(Packet& packet);
			void HandlePositionAndLook(Packet& pData);
			void HandleMount(Packet& pData);
			void HandleUnmount(Packet& pData);
			void HandleCharacterInfo(Packet& pData);
			void HandleChatMessage(Packet& pData);
			void HandleShardPick(Packet& pData);
			/// End Handlers
			/// Database callbacks
			void HandleUserLoad();
			/// End database callbacks

		private:

			typedef  void(Session::*CallBack)(Packet&);
			typedef  void(Session::*QueryCallback)();

	// NETWORK
			enum { header_length = 4 };
			std::string outbound_header_;
			std::string outbound_data_;
			char inbound_header_[header_length];
			std::vector<char>  inbound_data_;

			Packet mReceivingPacket;
			Concurrency::concurrent_queue<Packet> mPackets;
			PacketQueue mToSend;

			boost::asio::ip::tcp::socket	mSocket;
	// ~NETWORK

			Server*							mServer;
			Game::World*					mWorld;

			std::list<std::shared_ptr<Session>> mInRange;

			bool							mAuth;
			clock_t mTimeSinceLastMessage;

			Game::Player mPlayer;
			Entity::Account mAccount;

			static std::unordered_map<unsigned int, CallBack> mAuthHandlers;
			static std::unordered_map<unsigned int, CallBack> mHandlers;
			static std::unordered_map<unsigned int, QueryCallback> mQueryHandlers;
		};
	}
}