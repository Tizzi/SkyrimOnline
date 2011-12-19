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