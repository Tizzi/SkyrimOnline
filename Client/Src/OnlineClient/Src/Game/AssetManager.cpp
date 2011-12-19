#include "stdafx.h"
#include "AssetManager.h"

namespace SkyrimOnline
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		AssetManager::AssetManager()
		{
			std::ifstream db("./Data/Online/User/Assets.db");
			if(db.is_open())
				while(!db.eof())
				{
					std::string line;
					std::getline(db, line);

					try
					{
						uint32_t id = std::stoul(line);
						if(id)
						{
							TESObjectREFR* form = (TESObjectREFR*)dyn_cast(::Game::GetFormById(id),"TESForm","TESObjectREFR");
							if(form)
							{
								mAssets.push_back(id);
								ObjectReference::Delete(form);
							}
						}
					}
					catch(std::exception& e)
					{
						//Log::GetInstance()->Error(e.what());
					}
				}
			Write();
		}
		//--------------------------------------------------------------------------------
		AssetManager::~AssetManager()
		{
		}
		//--------------------------------------------------------------------------------
		void AssetManager::Add(TESObjectREFR* pAsset)
		{
			auto itor = std::find(mAssets.begin(), mAssets.end(), Form::GetFormID((TESForm*)pAsset));
			if(itor == mAssets.end())
			{
				mAssets.push_back(Form::GetFormID((TESForm*)pAsset));
				Write();
			}
		}
		//--------------------------------------------------------------------------------
		void AssetManager::Remove(TESObjectREFR* pAsset)
		{
			auto itor = std::find(mAssets.begin(), mAssets.end(), Form::GetFormID((TESForm*)pAsset));
			if(itor != mAssets.end())
			{
				mAssets.erase(itor);
				Write();
			}
		}
		//--------------------------------------------------------------------------------
		void AssetManager::Write()
		{
			std::ofstream db("./Data/Online/User/Assets.db",std::ios::trunc);
			auto end = mAssets.end();
			for(auto itor = mAssets.begin(); itor != end; ++itor)
			{
				db << *itor << std::endl;
			}
		}
		//--------------------------------------------------------------------------------
	}
}