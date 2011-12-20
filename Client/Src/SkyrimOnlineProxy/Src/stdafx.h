#pragma once

#define _WIN32_WINNT 0x0501
#define DIRECTINPUT_VERSION 0x0800

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>

#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <deque>
#include <concurrent_queue.h>
#include <unordered_map>

#include <Winuser.h>
#include <d3d9.h>

#include <common/skyscript.h>
#include <common/obscript.h>
#include <common/types.h>
#include <common/enums.h>
#include <common/plugin.h>
#include <common/Log.h>
#include <common/Utils.h>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )