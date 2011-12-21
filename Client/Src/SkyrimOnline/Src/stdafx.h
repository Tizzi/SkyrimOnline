/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

#pragma once

#define _WIN32_WINNT 0x0501
#define DIRECTINPUT_VERSION 0x0800

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/timer.hpp>

#include <Game/data.h>

#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <deque>
#include <concurrent_queue.h>
#include <unordered_map>

#include <Winuser.h>

#include <dinput.h>

//#include <ois/OIS.h>

#include <MyGUI.h>
#include <MyGUI_DirectXPlatform.h>

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