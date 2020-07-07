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
	return read_photo(path, cv::IMREAD_COLOR);
}

CVMat smsc_cvutil::read_photo(const std::string& path, const cv::ImreadModes mode)
{
	CVMat mat{ false };
	if (is_file_ok(path)) {
		try {
			mat.mat = cv::imread(path, mode);
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

void smsc_cvutil::open_photo_with_highgui(const std::string& path)
{
	smsc_cvutil::CVMat mat = smsc_cvutil::read_photo(path);
	if (mat.is_ok && !mat.mat.empty()) {
		cv::namedWindow("Preview", cv::WINDOW_AUTOSIZE);
		cv::imshow("Preview", mat.mat);
	}
}
