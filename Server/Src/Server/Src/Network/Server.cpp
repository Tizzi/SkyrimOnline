#include "stdafx.h"
#include <Network/Server.h>

using boost::asio::ip::tcp;

namespace Skyrim
{
	namespace Network
	{
		//---------------------------------------------------------------------
		Server::Server(unsigned short pPort)
			:mAcceptor(*new boost::asio::io_service, tcp::endpoint(tcp::v4(), pPort)), mDBWorkQueue(4), mStarted(false), mID(0),mMaxConnections(0)
		{
			System::Log::GetInstance()->Print("                            Skyrim Online         ");
			System::Log::GetInstance()->Print("Memory model : " + std::to_string((unsigned long long)sizeof(void*) * 8) + " bits				   ");
			System::Log::GetInstance()->Print("Running with : - 4 Database threads				               ");
			System::Log::GetInstance()->Print("               - 1 Network thread                                ");
			System::Log::GetInstance()->Print("               - 1 Event thread                                  ");
			System::Log::GetInstance()->Print("");
		}
		//---------------------------------------------------------------------
		void Server::Start()
		{
			System::Log::GetInstance()->Print("Waiting for connections.");
			Session::Setup();

			AddShard(new Game::World("Skyrim Online English", true));
			AddShard(new Game::World("Skyrim Online Others", true));

			new boost::thread(boost::bind(&boost::asio::io_service::run, &mAcceptor.get_io_service()));
			Accept();
			mStarted = true;
			Run();
		}
		//---------------------------------------------------------------------
		void Server::Run()
		{
			while(1)
			{
				// This thread doesn't need to be very responsive
				Sleep(10);

				long time = clock();
				mGuard.lock();
				auto sessionCopy(mSessions);
				mGuard.unlock();

				// Work with authenticating sessions
				std::for_each(sessionCopy.begin(), sessionCopy.end(),
					[this](Session::pointer pSession)
				{
					// Run must be synchronous
					pSession->Run();
				});

				// Go through world and delete dead ones
				auto end = mWorlds.end();
				for(auto itor = mWorlds.begin(); itor != end; ++itor)
				{
					if((itor)->second->IsMarkedForDelete())
					{
						delete (itor)->second;
						itor = mWorlds.erase(itor);
					}
				}

				System::Log::GetInstance()->Update();
			}
		}
		//---------------------------------------------------------------------
		void Server::Stop()
		{
		}
		//---------------------------------------------------------------------
		System::DBWorkQueue* Server::GetDatabaseWorkQueue()
		{
			return &mDBWorkQueue;
		}
		//---------------------------------------------------------------------
		void Server::Accept()
		{
			Session::pointer session = std::make_shared<Session>(mAcceptor.get_io_service(), this);
			mAcceptor.async_accept(session->GetSocket(),
				boost::bind(&Server::HandleAccept, this,
				session, boost::asio::placeholders::error));
		}
		//---------------------------------------------------------------------
		void Server::Remove(Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
				mSessions.erase(itor);
			else
			{
				pPlayer->GetWorld()->Remove(pPlayer);
			}
		}
		//---------------------------------------------------------------------
		void Server::HandleAccept(Session::pointer pSession, const boost::system::error_code& pError)
		{
			if(!pError)
			{
				mGuard.lock();
				mSessions.push_back(pSession);
				mGuard.unlock();

				pSession->Start();
			}
			else
			{
				std::cerr << pError.message().c_str() << std::endl;
			}
			Accept();
		}
		//---------------------------------------------------------------------
		unsigned int Server::Count()
		{
			unsigned int total = (unsigned int)mSessions.size();
			auto end = mWorlds.end();
			for(auto itor = mWorlds.begin(); itor != end; ++itor)
			{
				total += itor->second->Count();
			}
			mMaxConnections = std::max(total,mMaxConnections);
			return total;
		}
		//---------------------------------------------------------------------
		unsigned int Server::Peak()
		{
			return mMaxConnections;
		}
		//---------------------------------------------------------------------
		void Server::SendShardList(Session::pointer pPlayer)
		{
			Packet packet;
			packet.Opcode = SMSG_SHARD_LIST;
			packet.Push((unsigned int)mWorlds.size());

			auto end = mWorlds.end();
			unsigned int i = 0;
			for(auto itor = mWorlds.begin(); itor != end; ++itor)
			{
				packet.Push(itor->second->GetName());
				packet.Push((unsigned int)0);
				++i;
			}
			pPlayer->Write(packet);
		}
		//---------------------------------------------------------------------
		void Server::MoveToWorld(const std::string& pWorldIndex, Session::pointer pPlayer)
		{
			{
				boost::mutex::scoped_lock lock(mGuard);

				auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
				if(itor != mSessions.end())
					mSessions.erase(itor);
			}
			auto world = mWorlds[pWorldIndex];
			if(world)
			{
				world->Add(pPlayer);
			}
		}
		//---------------------------------------------------------------------
		void Server::AddShard(Game::World* pWorld)
		{
			mWorlds[pWorld->GetName()] = pWorld;
		}
		//---------------------------------------------------------------------
	}
}