#include "str_util.h"
#include "time_util.h"
#include "c_util.h"
string smsc_str_util::get_file_name_from_uri(const string& path)
{
	if (path.length() == 0) {
		return string();
	}
	string p = string(path);
	int position = p.find("\\");
	while (position != string::npos) {
		p.replace(position, 1, "/");
		position = p.find("\\");
	}
	position = p.find_last_of("/");
	if (position != string::npos) {
		return p.substr(position+1);
	}
	return p;
}

string smsc_str_util::get_file_parent_path_from_uri(const string& uri)
{
	if (uri.length() == 0) {
		return string();
	}
	string p = string(uri);
	int position = p.find("\\");
	while (position != string::npos) {
		p.replace(position, 1, "/");
		position = p.find("\\");
	}
	position = p.find_last_of("/");
	if (position != string::npos) {
		return p.substr(0,position+1);
	}
	return p;
}

string smsc_str_util::get_file_extention(const string& path)
{
	if (path.length() == 0) {
		return string();
	}
	int pos = path.find(".");
	if (pos != string::npos) {
		return path.substr(pos + 1);
	}
	return path;
}

const static string ALTER_SYM = "altered_at_";
string smsc_str_util::append_uri_with_ts(const string& uri)
{
	string path = smsc_str_util::get_file_parent_path_from_uri(uri);
	string name = smsc_str_util::get_file_name_from_uri(uri);
	path.append(ALTER_SYM).append(smsc_time_util::get_ts_str()).append("_").append(name);
	return path;
}

string smsc_str_util::substr_after_nth_char(const string& str,const char& symbol, const int& nth)
{
	const char* chars = str.c_str();
	int index = -1;
	int n = 0;
	int m = -1;
	while (n < nth && *chars != '\0') {
		if (*chars++ == symbol) {
			n++;
			m = ++index;
		}
		else {
			index++;
		}
	}
	if (m >= 0) {
		return str.substr(m+1);
	}
	return str;
}

string smsc_str_util::substr_before_nth_char(const string& str, const char& symbol, const int& nth)
{
	const char* chars = str.c_str();
	int index = -1;
	int n = 0;
	int m = -1;
	while (n < nth && *chars != '\0') {
		if (*chars++ == symbol) {
			n++;
			m = ++index;
		}
		else {
			index++;
		}
	}
	if (m >= 0) {
		return str.substr(0,m);
	}
	return str;
}
