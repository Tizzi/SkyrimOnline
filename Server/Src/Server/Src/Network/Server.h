#pragma once

#include <Network/Session.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>
#include <Game/World.h>

namespace Skyrim
{
	namespace Network
	{
		class Server
			: public System::EventListener,
			public std::enable_shared_from_this<Server>
		{
		public:

			Server(unsigned short pPort);
			void Start();
			void Run();
			void Stop();

			// MUST NEVER BE CALLED
			// CALL Close on Session instead
			void Remove(Session::pointer pSession);

			System::DBWorkQueue* GetDatabaseWorkQueue();

			virtual void OnEvent(std::shared_ptr<System::Event> pEvent)
			{
				if(!mStarted)
				{
					mGuard.unlock();
				}
			}

			unsigned int Count();
			unsigned int Peak();

			void DispatchToAll(Packet&);
			void DispatchToAllButMe(Packet&, Session::pointer pPlayer);
			void SendShardList(Session::pointer pPlayer);

			void MoveToWorld(const std::string& pWorldIndex, Session::pointer pPlayer);

		protected:

			void AddShard(Game::World* pWorld);

			void Accept();
			void HandleAccept(Session::pointer pSession, const boost::system::error_code& pError);

		private:

			boost::asio::ip::tcp::acceptor mAcceptor;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;
			std::map<std::string,Game::World*>		mWorlds;
			System::DBWorkQueue mDBWorkQueue;

			unsigned int mMaxConnections;

			bool mStarted;

			unsigned int mID;
		};
	}
}