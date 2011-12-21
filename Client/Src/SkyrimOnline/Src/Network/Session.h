/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#include "Packet.h"

using boost::asio::ip::tcp;

namespace SkyrimOnline
{
	namespace Network
	{
		typedef std::deque<Packet> PacketQueue;

		class Session
		{
		public:

			typedef boost::shared_ptr<Session> pointer;

			Session();
			~Session();

			void Start();
			void Write(const Packet& msg);
			void close();
			bool IsOnline();
			void Run();

			static void Init();
			static Network::Session* Create()
			{
				return new Network::Session();
			}

		protected:

			void HandleNewPlayer(Packet&);
			void HandlePlayerCount(Packet&);
			void HandlePlayerSpawn(Packet&);
			void HandlePlayerMoveAndLook(Packet&);
			void HandlePlayerRemove(Packet&);
			void HandleChatMessage(Packet&);
			void HandleShardList(Packet&);
			void HandleShardHandShake(Packet&);
			void HandleTimeSync(Packet&);
			void HandleWeatherSync(Packet&);
			void HandleMount(Packet&);
			void HandleUnmount(Packet&);

			void async_write(const Packet& t)
			{
				++count_;
				// Serialize the data first so we know how large it is.
				std::ostringstream archive_stream;
				boost::archive::text_oarchive archive(archive_stream);
				archive << t;
				outbound_data_ = archive_stream.str();

				unsigned int size = outbound_data_.size();
				// Format the header.
				std::string header_stream;

				outbound_header_.clear();
				outbound_header_.append((char*)&size,4);

				if (outbound_header_.size() != header_length)
				{
					return;
				}

				// Write the serialized data to the socket. We use "gather-write" to send
				// both the header and the data in a single write operation.
				std::vector<boost::asio::const_buffer> buffers;
				buffers.push_back(boost::asio::buffer(outbound_header_));
				buffers.push_back(boost::asio::buffer(outbound_data_));
				boost::asio::async_write(*socket_, buffers, boost::bind(&Session::handle_write, this, boost::asio::placeholders::error));
			}

			void async_read()
			{
				++count_;
				boost::asio::async_read(*socket_, boost::asio::buffer(inbound_header_),
					boost::bind(&Session::handle_read_header,
					this, boost::asio::placeholders::error));
			}

			void handle_read_header(const boost::system::error_code& e)
			{
				if (e)
				{
					--count_;
					handle_read(e);
					return;
				}
				else
				{
					std::size_t inbound_data_size = *(unsigned int*)inbound_header_;
					if (inbound_data_size > 1 << 16)
					{
						return;
					}

					// Start an asynchronous call to receive the data.
					inbound_data_.resize(inbound_data_size);

					boost::asio::async_read(*socket_, boost::asio::buffer(inbound_data_),
						boost::bind(&Session::handle_read_data, this,
						boost::asio::placeholders::error));
				}
			}

			void handle_read_data(const boost::system::error_code& e)
			{
				if (e)
				{
					--count_;
					handle_read(e);
				}
				else
				{
					// Extract the data structure from the data just received.
					try
					{
						std::string archive_data(&inbound_data_[0], inbound_data_.size());
						std::istringstream archive_stream(archive_data);
						boost::archive::text_iarchive archive(archive_stream);
						archive >> mReceivingPacket;
					}
					catch (...)
					{
						--count_;
						return;
					}

					--count_;
					handle_read(e);
				}
			}

		private:

			typedef  void(Session::*CallBack)(Packet&);

			void handle_resolve(tcp::resolver::iterator endpoint_iterator);
			void handle_connect(const boost::system::error_code& error);
			void handle_read(const boost::system::error_code& error);
			void do_write(Packet msg);
			void handle_write(const boost::system::error_code& error);
			void do_close();

		private:

			size_t count_;
			tcp::socket* socket_;
			tcp::resolver* resolver_;
			boost::asio::io_service* mIoService;
			boost::asio::io_service::work* mWork;
			/// The size of a fixed length header.
			enum { header_length = 4 };

			/// Holds an outbound header.
			std::string outbound_header_;

			/// Holds the outbound data.
			std::string outbound_data_;

			/// Holds an inbound header.
			char inbound_header_[header_length];

			/// Holds the inbound data.
			std::vector<char> inbound_data_;
			boost::thread* mThread;

			Packet mReceivingPacket;

			PacketQueue mToSend;
			Concurrency::concurrent_queue<Packet> mPackets;
			bool mConnected;

			static std::unordered_map<unsigned int, CallBack> mHandlers;
		};
	}
}