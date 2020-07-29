#include "cv_util.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include <opencv2/imgproc.hpp>
#include "str_util.h"
#include "io_util.h"
using namespace cv;
using namespace std;
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
		cv::waitKey(0);
	}
}

void smsc_cvutil::show_photo(const CVMat& cv_mat)
{
	if (cv_mat.is_ok) {
		show_photo(cv_mat.mat);
	}
}

void smsc_cvutil::show_photo(const cv::Mat& mat)
{
	cv::namedWindow("Preview", cv::WINDOW_AUTOSIZE);
	cv::imshow("Preview", mat);
	cv::waitKey(0);
}

static void filter2D_process_1(const string& file);
void smsc_cvutil::apply_filter2D_to_dir(const string& dir)
{
	vector<string> files = smsc_ioutil::list_files(dir, true);
	for (string file : files) {
		cout << "processing " << file << endl;
		filter2D_process_1(file);
	}
}


static void filter2D_process_1(const string& file) {
	CVMat wrapper = read_photo(file);
	if (wrapper.is_ok) {
		Mat mat = wrapper.mat;
		Mat copy = Mat(mat);
		Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
			-1, 5, -1,
			0, -1, 0);
		cv::filter2D(mat, copy, mat.depth(), kernel);
		imwrite(smsc_str_util::append_uri_with_ts(file), copy);
	}
}
