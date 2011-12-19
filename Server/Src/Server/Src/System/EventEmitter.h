#pragma once

#include <System/EventListener.h>
#include <System/Event.h>

namespace Skyrim{
	namespace System
	{
		struct EventEmitter
		{
			void Add(std::shared_ptr<EventListener> pListener);
			void Remove(std::shared_ptr<EventListener> pListener);
			void Dispatch(std::shared_ptr<Event> pEvent);

		private:

			std::vector<std::shared_ptr<EventListener>> mListeners;
			boost::mutex mGuard;
		};
	}
}