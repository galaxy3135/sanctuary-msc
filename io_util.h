#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace smsc_ioutil {
	vector<string> read_file_lines(const string& file_path);

	void print_file_lines(const string& file_path);

	vector<string> list_files(const string& directory, const bool& is_recursive);
}
