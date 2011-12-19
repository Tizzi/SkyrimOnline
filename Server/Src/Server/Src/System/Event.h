#pragma once

namespace Skyrim{
	namespace System
	{
		struct Event
		{
			typedef std::shared_ptr<Event> pointer;

			enum Type{
				DATAOBJECT_LOAD,
				DATAOBJECT_LOAD_FAIL,
				DATAOBJECT_SAVE,
				DATAOBJECT_SAVE_FAIL
			};
			virtual Type type() = 0;
			unsigned int userData;
		};
	}
}