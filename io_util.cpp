#include "io_util.h"
#include <fstream>
#include <boost/filesystem.hpp>

vector<string> smsc_ioutil::read_file_lines(const string& file_path)
{
	vector<string> vec = vector<string>();
	ifstream fs = ifstream(file_path,ios::_Nocreate);
	if (fs.good()) 
	{
		string str;
		while (getline(fs,str)) 
		{
			vec.push_back(str);
		}
	}
	return vec;
}

void smsc_ioutil::print_file_lines(const string& file_path)
{
	ifstream fs = ifstream(file_path, ios::_Nocreate);
	if (fs.good()) 
	{
		string str;
		while (getline(fs, str)) 
		{
			std::cout << str << std::endl;
		}
	}
}

vector<string> smsc_ioutil::list_files(const string& directory, const bool& is_recursive)
{
	vector<string> vec = vector<string>();
	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory)) 
	{
		auto iter = boost::filesystem::directory_iterator(directory, boost::filesystem::directory_options::skip_permission_denied);
		for (boost::filesystem::directory_entry& x : iter) 
		{
			if (boost::filesystem::is_regular_file(x)) 
			{
				vec.push_back(x.path().string());
				//cout << x.path().string() << endl;
			}
			else if (is_recursive && boost::filesystem::is_directory(x))
			{
				vector<string> sub_vec = list_files(x.path().string(), true);
				vec.insert(vec.end(), sub_vec.begin(), sub_vec.end());
			}
			
		}
	}
	return vec;
}
