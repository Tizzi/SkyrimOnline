#include "stdafx.h"
#include "World.h"
#include <Network/Packet.h>

namespace Skyrim{
	namespace Game
	{
		//---------------------------------------------------------------------
		World::World(const std::string& pName, bool pPersistant)
			:mName(pName), mWorldThread(nullptr), mPersistant(pPersistant)
		{
		}
		//---------------------------------------------------------------------
		void World::Run()
		{
			while(1)
			{
				float elapsed = (float)mTimer.elapsed();
				if(mSessions.size() > 0)
				{
					mTimeManager.Update(elapsed);

					mTimer.restart();
					mGuard.lock();
					auto sessionCopy(mSessions);
					mGuard.unlock();

					std::for_each(sessionCopy.begin(), sessionCopy.end(),
						[this](Network::Session::pointer pSession)
					{
						pSession->Run();
					});
				}
				else if(elapsed > 120)
				{
					boost::mutex::scoped_lock(mReleaseGuard);
					delete mWorldThread;
					mWorldThread = nullptr;
					return;
				}
			}
		}
		//---------------------------------------------------------------------
		void World::Add(Network::Session::pointer pPlayer)
		{
			{
				boost::mutex::scoped_lock lock(mGuard);
				mSessions.push_back(pPlayer);
			}
			{
				boost::mutex::scoped_lock(mReleaseGuard);
				if(mWorldThread == nullptr)
				{
					mWorldThread = new boost::thread(std::bind(&World::Run,this));
				}
			}

			pPlayer->SetWorld(this);

			Network::Packet packet;
			packet.Opcode = SMSG_SHARD_HANDSHAKE;
			packet.Push((unsigned int)1);
			pPlayer->Write(packet);

			SendTimeSync(pPlayer);
			SendWeatherSync(pPlayer);
		}
		//---------------------------------------------------------------------
		void World::Remove(Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);
			auto itor = std::find(mSessions.begin(), mSessions.end(), pPlayer);
			if(itor != mSessions.end())
				mSessions.erase(itor);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&pPlayer](Network::Session::pointer pSession)
			{
				pSession->Remove(pPlayer);
			});
		}
		//---------------------------------------------------------------------
		void World::DispatchPlayerMoveAndLook(Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&pPlayer](Network::Session::pointer pSession)
			{
				if(pSession != pPlayer)
				{
					pSession->HandlePlayerEvent(pPlayer);
				}
			});
		}
		//---------------------------------------------------------------------
		void World::DispatchToAll(Network::Packet& data)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&data](Network::Session::pointer pSession)
			{
				pSession->Write(data);
			});
		}
		//---------------------------------------------------------------------
		void World::DispatchToAllButMe(Network::Packet& data, Network::Session::pointer pPlayer)
		{
			boost::mutex::scoped_lock lock(mGuard);

			std::for_each(mSessions.begin(), mSessions.end(),
				[this,&pPlayer,&data](Network::Session::pointer pSession)
			{
				if(pSession != pPlayer)
				{
					pSession->Write(data);
				}
			});
		}
		//---------------------------------------------------------------------
		bool World::IsMarkedForDelete()
		{
			return (mWorldThread == nullptr && mTimer.elapsed() >= 180 && !mPersistant);
		}
		//---------------------------------------------------------------------
		std::string World::GetName()
		{
			return mName;
		}
		//---------------------------------------------------------------------
		unsigned int World::Count()
		{
			return mSessions.size();
		}
		//---------------------------------------------------------------------
	}
}