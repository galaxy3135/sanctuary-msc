#include "cv_util.h";
#include "opencv2/core.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
using namespace smsc_cvutil;

namespace smsc_cv_pixel {
	void proc_pixels(cv::Mat mat, const function<void(Vec3b&)>& func);

	void proc_pixels(cv::Mat mat, const function<void(Vec3b&, int& row, int& col)>& func);

	/*
	对每个像素进行乘法运算,
	factor_b 蓝色运算系数
	factor_g 绿色运算系数
	factor_r 红色运算系数
	*/
	void pixel_multiplie(float factor_b, float factor_g, float factor_r, cv::Mat src, const string& dest_path);
}