#pragma once
#include <string>
using namespace std;

namespace smsc_str_util {
	string get_file_name_from_uri(const string& uri);

	string get_file_parent_path_from_uri(const string& uri);

	string get_file_extention(const string& path);

	string append_uri_with_ts(const string& uri);

	string substr_after_nth_char(const string& str, const char& symbol, const int& nth);

	string substr_before_nth_char(const string& str, const char& symbol, const int& nth);
}

