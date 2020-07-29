#include "pixel_proc.h"

void smsc_cv_pixel::proc_pixels(cv::Mat mat, const function<void(Vec3b&)>& func)
{
	int rows = mat.rows;
	int cols = mat.cols;
	int i, j;
	for (i = 0; i < rows; i++) {
		Vec3b* r = mat.ptr<Vec3b>(i);
		for (j = 0; j < cols; j++) {
			Vec3b& pixel = *r++;
			func(pixel);
		}
	}
}

void smsc_cv_pixel::proc_pixels(cv::Mat mat, const function<void(Vec3b&, int& row, int& col)>& func)
{
	int rows = mat.rows;
	int cols = mat.cols;
	int i, j;
	for (i = 0; i < rows; i++) {
		Vec3b* r = mat.ptr<Vec3b>(i);
		for (j = 0; j < cols; j++) {
			Vec3b& pixel = *r++;
			func(pixel,i,j);
		}
	}
}

void smsc_cv_pixel::pixel_multiplie(float factor_b,float factor_g,float factor_r, cv::Mat src, const string& dest_path)
{
	smsc_cv_pixel::proc_pixels(src, [&](Vec3b& pixel) mutable -> void
		{
			uchar B = pixel[0];
			uchar G = pixel[1];
			uchar R = pixel[2];
			pixel[0] = B * factor_b;
			pixel[1] = G * factor_g;
			pixel[2] = R * factor_r;
		});
	imwrite(dest_path, src);
}
