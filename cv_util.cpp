#include "cv_util.h"
#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include <opencv2/imgproc.hpp>
#include "str_util.h"
#include "io_util.h"
#include <cassert>
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

static double distance(const double x1, const double y1, const double x2, const double y2)//两点之间距离，这里用欧式距离
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);//只需比较大小，返回距离平方即可
}

void smsc_cvutil::nearest_intertoplation_veb3b(cv::Mat& src, cv::Mat& dst, const int rows, const int cols)
{
	//比例尺
	const double scale_row = static_cast<double>(src.rows) / rows;
	const double scale_col = static_cast<double>(src.rows) / cols;

	//扩展src到dst
	dst = cv::Mat(rows, cols, src.type());
	//assert(src.channels() == 1 && dst.channels() == 1);

	for (int i = 0; i < rows; ++i)//dst的行
		for (int j = 0; j < cols; ++j)//dst的列
		{
			//求插值的四个点
			double y = (i + 0.5) * scale_row + 0.5;
			double x = (j + 0.5) * scale_col + 0.5;
			int x1 = static_cast<int>(x);//col对应x
			if (x1 >= (src.cols - 2)) x1 = src.cols - 2;//防止越界
			int x2 = x1 + 1;
			int y1 = static_cast<int>(y);//row对应y
			if (y1 >= (src.rows - 2))  y1 = src.rows - 2;
			int y2 = y1 + 1;
			//根据目标图像的像素点（浮点坐标）找到原始图像中的4个像素点，取距离该像素点最近的一个原始像素值作为该点的值。
			assert(0 < x2 && x2 < src.cols && 0 < y2 && y2 < src.rows);
			std::vector<double> dist(4);
			dist[0] = distance(x, y, x1, y1);
			dist[1] = distance(x, y, x2, y1);
			dist[2] = distance(x, y, x1, y2);
			dist[3] = distance(x, y, x2, y2);

			int min_val = dist[0];
			int min_index = 0;
			for (int i = 1; i < dist.size(); ++i)
				if (min_val > dist[i])
				{
					min_val = dist[i];
					min_index = i;
				}

			switch (min_index)
			{
			case 0:
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y1, x1);
				break;
			case 1:
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y1, x2);
				break;
			case 2:
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y2, x1);
				break;
			case 3:
				dst.at<Vec3b>(i, j) = src.at<Vec3b>(y2, x2);
				break;
			default:
				assert(false);
			}
		}
}

void smsc_cvutil::bilinear_intertpolatioin_grey(cv::Mat& src, cv::Mat& dst, const int rows, const int cols)
{
	//比例尺
	const double scale_row = static_cast<double>(src.rows) / rows;
	const double scale_col = static_cast<double>(src.rows) / cols;

	//扩展src到dst
	dst = cv::Mat(rows, cols, src.type());
	//assert(src.channels() == 1 && dst.channels() == 1);

	for (int i = 0; i < rows; ++i)//dst的行
		for (int j = 0; j < cols; ++j)//dst的列
		{
			//求插值的四个点
			double y = (i + 0.5) * scale_row + 0.5;
			double x = (j + 0.5) * scale_col + 0.5;
			int x1 = static_cast<int>(x);//col对应x
			if (x1 >= (src.cols - 2)) x1 = src.cols - 2;//防止越界
			int x2 = x1 + 1;
			int y1 = static_cast<int>(y);//row对应y
			if (y1 >= (src.rows - 2))  y1 = src.rows - 2;
			int y2 = y1 + 1;

			assert(0 < x2 && x2 < src.cols && 0 < y2 && y2 < src.rows);
			//插值公式,参考维基百科矩阵相乘的公式https://zh.wikipedia.org/wiki/%E5%8F%8C%E7%BA%BF%E6%80%A7%E6%8F%92%E5%80%BC

			cv::Matx12d matx = { x2 - x, x - x1 };
			cv::Matx22d matf = { static_cast<double>(src.at<uchar>(y1, x1)), static_cast<double>(src.at<uchar>(y2, x1)),
								 static_cast<double>(src.at<uchar>(y1, x2)), static_cast<double>(src.at<uchar>(y2, x2)) };
			cv::Matx21d maty = {
				y2 - y,
				y - y1
			};

			auto  val = (matx * matf * maty);
			dst.at<uchar>(i, j) = val(0, 0);
		}
}

void smsc_cvutil::bilinear_intertpolatioin_vec3b(cv::Mat& src, cv::Mat& dst, const int rows, const int cols)
{
	//比例尺
	const double scale_row = static_cast<double>(src.rows) / rows;
	const double scale_col = static_cast<double>(src.rows) / cols;

	//扩展src到dst
	dst = cv::Mat(rows, cols, src.type());
	//assert(src.channels() == 1 && dst.channels() == 1);

	for (int i = 0; i < rows; ++i)//dst的行
		for (int j = 0; j < cols; ++j)//dst的列
		{
			//求插值的四个点
			double y = (i + 0.5) * scale_row + 0.5;
			double x = (j + 0.5) * scale_col + 0.5;
			int x1 = static_cast<int>(x);//col对应x
			if (x1 >= (src.cols - 2)) x1 = src.cols - 2;//防止越界
			int x2 = x1 + 1;
			int y1 = static_cast<int>(y);//row对应y
			if (y1 >= (src.rows - 2))  y1 = src.rows - 2;
			int y2 = y1 + 1;


			cv::Matx12d matx = { x2 - x, x - x1 };
			cv::Matx22d matf_b = { static_cast<double>(src.at<Vec3b>(y1, x1)[0]), static_cast<double>(src.at<Vec3b>(y2, x1)[0]),
								 static_cast<double>(src.at<Vec3b>(y1, x2)[0]), static_cast<double>(src.at<Vec3b>(y2, x2)[0]) };

			cv::Matx22d matf_g = { static_cast<double>(src.at<Vec3b>(y1, x1)[1]), static_cast<double>(src.at<Vec3b>(y2, x1)[1]),
							 static_cast<double>(src.at<Vec3b>(y1, x2)[1]), static_cast<double>(src.at<Vec3b>(y2, x2)[1]) };

			cv::Matx22d matf_r = { static_cast<double>(src.at<Vec3b>(y1, x1)[2]), static_cast<double>(src.at<Vec3b>(y2, x1)[2]),
							 static_cast<double>(src.at<Vec3b>(y1, x2)[2]), static_cast<double>(src.at<Vec3b>(y2, x2)[2]) };

			cv::Matx21d maty = {
				y2 - y,
				y - y1
			};

			auto  val_b = (matx * matf_b * maty);
			auto  val_g = (matx * matf_g * maty);
			auto  val_r = (matx * matf_r * maty);
			dst.at<Vec3b>(i, j)[0] = val_b(0, 0);
			dst.at<Vec3b>(i, j)[1] = val_g(0, 0);
			dst.at<Vec3b>(i, j)[2] = val_r(0, 0);
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
