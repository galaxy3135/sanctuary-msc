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
	��ÿ�����ؽ��г˷�����,
	factor_b ��ɫ����ϵ��
	factor_g ��ɫ����ϵ��
	factor_r ��ɫ����ϵ��
	*/
	void pixel_multiplie(float factor_b, float factor_g, float factor_r, cv::Mat src, const string& dest_path);
}