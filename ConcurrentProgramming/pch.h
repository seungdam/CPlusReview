#pragma once

#include <iostream>
#include <thread>
#include <utility>
#include <atomic>
#include <mutex>
#include <vector>
#include <sstream>
#include <iomanip>
#include <random>

// make alias of basic data types

using int8   = __int8;
using int16  = __int16;
using int32  = __int32;
using int64  = __int64;
using uint8  = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#define t_set "\033["
#define t_reset "\033[0m"
#define t_bold "1;"

#define t_r "31m"
#define t_g "32m"
#define t_y "33m"
#define t_b "34m"
#define t_p "35m"
#define t_c "36m"

