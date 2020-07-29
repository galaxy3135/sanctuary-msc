#include "time_util.h"
#include <sstream>

time_t smsc_time_util::get_ts()
{
	time_t a;
	time(&a);
	return a;
}

std::string smsc_time_util::get_ts_str()
{
	std::stringstream stream;
	std::string result;
	stream << get_ts();
	stream >> result;
	return result;
}
