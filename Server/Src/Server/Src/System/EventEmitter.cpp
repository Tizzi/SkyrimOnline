/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

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