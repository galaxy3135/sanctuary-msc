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
#include "c_util.h";
#include <cassert>
#include <malloc.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;
using namespace smsc_cvutil;
using namespace smsc_ioutil;

template<typename T>
static string force_cast_int(T val) {
	return string(val);
}

//int main()
//{
	//cout << char_length_of("12345") << endl;
	//char* txt_content = (char*)malloc(1000*sizeof(char));
	//char *txt_content = read_text_file("E:\\test.txt");
	//cout << txt_content << endl;
	//for (int i = 0; i < 100; i++) {
	//	*txt_content++ = '1';
	//}
	//cout << txt_content << endl;
	//cout << txt_content << endl;
	//free(txt_content);
	//free(txt_content);
	//cout << txt_content << endl;
	//free(txt_content);
	/*string path = "E:\\1\\2\\ssd.phg";
	string path2 = smsc_str_util::substr_before_nth_char(path, '\\', 2);
	cout << path2 << endl;
	string s = "test";
	const char* chars = s.c_str();
	while (*chars != '\0') {
		cout << *(chars++) << endl;
	}*/
	//cv::Mat img = cv::imread("E:\\smile.jpg", cv::IMREAD_COLOR);
	//if (img.empty()) return -1;
	//cv::Mat dst;
	//bilinear_intertpolatioin_vec3b(img, dst, 1000, 1000);
	////cv::imshow("img", img);
	////cv::imshow("dst", dst);
	//cv::imwrite("E:\\smile.jpg", dst);
	//cv::waitKey(0);
	//return 0;
//}


//int main(int argc, char** argv)
//{
//	string path = "E:\\TestResources\\testPic1.png";
//	string out = "E:\\TestResources\\testPic2_.png";
//	smsc_cvutil::adjust_saturation(path, out, 0.5, 1);
//	return 0;
//}
using namespace cv::ml;
int main(int argc, char** argv) {
	
	waitKey();
	return 0;
}


