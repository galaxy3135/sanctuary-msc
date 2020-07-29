#include "cv_util.h";
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp";
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "pixel_proc.h"
#include "str_util.h"
#include "time_util.h"
#include "io_util.h"
#include<cassert>
using namespace std;
using namespace cv;
using namespace smsc_cvutil;
using namespace smsc_ioutil;

int main()
{
	//cv::Mat img = cv::imread("E:\\smile.jpg", cv::IMREAD_COLOR);
	//if (img.empty()) return -1;
	//cv::Mat dst;
	//bilinear_intertpolatioin_vec3b(img, dst, 1000, 1000);
	////cv::imshow("img", img);
	////cv::imshow("dst", dst);
	//cv::imwrite("E:\\smile.jpg", dst);
	//cv::waitKey(0);
	return 0;
}


//int main(int argc, char** argv)
//{
//	string path = "E:\\TestResources\\testPic1.png";
//	string dir = "E:\\风景照片";
//	vector<string> files = list_files(dir,false);
//	string f1 = files[0];
//	string f2 = files.at(1);
//	double alpha = 0.5;
//	double beita;
//	double input;
//	Mat src1, src2, dst;
//	cout << " Simple Linear Blender " << endl;
//	cout << "-----------------------" << endl;
//	cout << "* Enter alpha [0.0-1.0]: ";
//	cin >> input;
//	// We use the alpha provided by the user if it is between 0 and 1
//	if (input >= 0 && input <= 1)
//	{
//		alpha = input;
//	}
//	src1 = imread(f2);
//	src2 = imread(f1);
//	if (src1.empty()) { cout << "Error loading src1" << endl; return EXIT_FAILURE; }
//	if (src2.empty()) { cout << "Error loading src2" << endl; return EXIT_FAILURE; }
//	beita = (1.0 - alpha);
//	addWeighted(src1, alpha, src2, beita, 0.0, dst);
//	imshow("Linear Blend", dst);
//	cv::waitKey(0); // Wait for a keystroke in the window
//	return 0;
//}


