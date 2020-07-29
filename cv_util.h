#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

namespace smsc_cvutil{
	struct mat_wrapper{
		bool is_ok;
		cv::Mat mat;
	};
	typedef struct mat_wrapper CVMat;
	CVMat read_photo(const std::string& path);
	CVMat read_photo(const std::string& path, const cv::ImreadModes mode);
	void open_photo_with_highgui(const std::string& path);
	void show_photo(const CVMat& cv_mat);
	void show_photo(const cv::Mat& mat);
	void apply_filter2D_to_dir(const std::string& dir);
}