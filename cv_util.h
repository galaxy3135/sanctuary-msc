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
	//最近邻域插值
	void nearest_intertoplation_veb3b(cv::Mat& src, cv::Mat& dst, const int rows, const int cols);
	//双线性插值 - 用于灰度图片
	void bilinear_intertpolatioin_grey(cv::Mat& src, cv::Mat& dst, const int rows, const int cols);
	//双线性插值 - 用于彩色BGR图片
	void bilinear_intertpolatioin_vec3b(cv::Mat& src, cv::Mat& dst, const int rows, const int cols);
	//
	void adjust_saturation(cv::Mat& src, cv::Mat& dst, double alpha, double beta);

	void adjust_saturation(const std::string& input_img, const std::string& output_img, double alpha, double beta);
}