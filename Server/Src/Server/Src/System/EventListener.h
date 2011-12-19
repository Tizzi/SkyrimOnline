#pragma once

#include <System/Event.h>

namespace Skyrim{
	namespace System
	{
		struct EventListener
		{
			virtual void OnEvent(std::shared_ptr<System::Event> pEvent)
			{
				mEvents.push(pEvent);
			}
		protected:
			Concurrency::concurrent_queue<std::shared_ptr<System::Event>> mEvents;
		};
	}
}