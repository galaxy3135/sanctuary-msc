#include "cv_util.h"
#include <fstream>
#include <iostream>
#include <exception>
using namespace smsc_cvutil;

static bool is_file_ok(const std::string& path) 
{
	std::fstream fs = std::fstream(path);
	return fs.good();
}

CVMat smsc_cvutil::read_photo(const std::string& path)
{
	CVMat mat{ false };
	if (is_file_ok(path)) {
		try {
			mat.mat = cv::imread(path, cv::IMREAD_COLOR);
			mat.is_ok = true;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			mat.is_ok = false;
			return mat;
		}
		return mat;
	}
	return mat;
}
