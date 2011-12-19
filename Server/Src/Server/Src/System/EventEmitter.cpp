#include "stdafx.h"
#include <System/EventEmitter.h>

namespace Skyrim{
	namespace System{
		//---------------------------------------------------------------------
		void EventEmitter::Add(std::shared_ptr<EventListener> pListener)
		{
			boost::mutex::scoped_lock lock(mGuard);
			mListeners.push_back(pListener);
		}
		//---------------------------------------------------------------------
		void EventEmitter::Remove(std::shared_ptr<EventListener> pListener)
		{
			boost::mutex::scoped_lock lock(mGuard);
			auto itor = std::find(mListeners.begin(), mListeners.end(), pListener);
			if(itor != mListeners.end())
				mListeners.erase(itor);
		}
		//---------------------------------------------------------------------
		void EventEmitter::Dispatch(std::shared_ptr<System::Event> pEvent)
		{
			boost::mutex::scoped_lock lock(mGuard);
			std::for_each(mListeners.begin(), mListeners.end(),
				[&](std::shared_ptr<EventListener> pListener)
				{
					pListener->OnEvent(pEvent);
				});
		}
		//---------------------------------------------------------------------
	}
}