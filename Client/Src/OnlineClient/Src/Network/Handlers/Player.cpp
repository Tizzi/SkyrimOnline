#include "stdafx.h"
#include <Network/Session.h>
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <Mod.h>

namespace SkyrimOnline
{
	namespace Network
	{
		//--------------------------------------------------------------------------------
		void Session::HandleNewPlayer(Packet& data)
		{
			try{
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[System] New player logged in, " + MyGUI::utility::toString(data.Int(0)) + " players online.");
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandleChatMessage(Packet& data)
		{
			try{
				std::ostringstream oss;
				oss << data.String(0);
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log(oss.str(),"#FFBF00");
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerCount(Packet& data)
		{
			try{
				unsigned int count = data.Int(0);
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[System] " + MyGUI::utility::toString(count) + " players online");
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerSpawn(Packet& data)
		{
			try{
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[System] Spawning player");
				unsigned int sex = data.Int(2);
				Mod::GetInstance().GetCharacterManager().Add(new Game::RemotePlayer(data.Int(0), data.Int(1), *(int*)&sex));
				auto player = Mod::GetInstance().GetCharacterManager().Get(data.Int(0));
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerMoveAndLook(Packet& data)
		{
			auto player = Mod::GetInstance().GetCharacterManager().Get(data.Int(0));
			player->InterpolateTo(data.Float(0), data.Float(1), data.Float(2), data.Float(3), data.Float(4), data.Float(5), data.Float(6));
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerRemove(Packet& data)
		{
			try{
				SkyrimOnline::Mod::GetInstance().GetInterface().GetChat()->Log("[System] Removing player");
				delete Mod::GetInstance().GetCharacterManager().Remove(
					Mod::GetInstance().GetCharacterManager().Get(data.Int(0)));
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandleMount(Packet& data)
		{
			try{
				auto remote = Mod::GetInstance().GetCharacterManager().Get(data.Int(0));
				if(remote)
				{
					remote->SetMount(0x10bf90);
				}
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandleUnmount(Packet& data)
		{
			try{
				auto remote = Mod::GetInstance().GetCharacterManager().Get(data.Int(0));
				if(remote)
				{
					remote->SetMount(0);
				}
			}
			catch(std::exception& e)
			{
				Log::GetInstance()->Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
	}
}