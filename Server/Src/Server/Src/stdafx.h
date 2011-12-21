/**
THE WORK (AS DEFINED BELOW) IS PROVIDED UNDER THE TERMS OF THIS CREATIVE COMMONS PUBLIC LICENSE ("CCPL" OR "LICENSE").
THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.

BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HERE, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
TO THE EXTENT THIS LICENSE MAY BE CONSIDERED TO BE A CONTRACT,
THE LICENSOR GRANTS YOU THE RIGHTS CONTAINED HERE IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
*/

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#define OTL_ODBC
//#define OTL_STREAM_NO_PRIVATE_BOOL_OPERATORS

#include "targetver.h"

#include <fstream>
#include <stdio.h>
#include <tchar.h>
#include <memory>
#include <iostream>
#include <boost/signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/tokenizer.hpp>
#include <boost/crc.hpp>
#include <ppl.h>
#include <concurrent_queue.h>
#include <random>
#include <unordered_map>
#include <DataBase/DataBase.h>
#include <DataBase/Column.h>
#include <DataBase/Query.h>
//#include <DataBase/otlv4.h>
#include <list>
#include <stdint.h>
#include <deque>
#include <boost/tuple/tuple.hpp>
#include <boost/timer.hpp>
#include <Game/enums.h>
#include <System/Log.h>

static const unsigned int Version = 6;