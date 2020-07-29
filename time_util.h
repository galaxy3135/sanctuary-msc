#pragma once
#include<time.h>
#include<string>

namespace smsc_time_util {
	time_t get_ts();
	std::string get_ts_str();
}