#include "str_util.h"
#include "time_util.h"
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

string smsc_str_util::append_uri_with_ts(const string& uri)
{
	string path = smsc_str_util::get_file_parent_path_from_uri(uri);
	string name = smsc_str_util::get_file_name_from_uri(uri);
	path.append(smsc_time_util::get_ts_str()).append("-").append(name);
	return path;
}
