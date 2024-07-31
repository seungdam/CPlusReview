#pragma once
#include <iostream>
#include <thread>
#include <utility>
#include <atomic>
#include <mutex>
#include <vector>


// make alias of basic data types

using int8   = __int8;
using int16  = __int16;
using int32  = __int32;
using int64  = __int64;
using uint8  = unsigned __int32;
using uint16 = unsigned __int32;
using uint32 = unsigned __int32;
using uint64 = unsigned __int32;

#define t_set "\033["
#define t_reset "\033[0m"
#define t_bold "1;"

#define t_color_r "31m"
#define t_color_g "32m"
#define t_color_y "33m"
#define t_color_b "34m"
#define t_color_p "35m"
#define t_color_c "36m"