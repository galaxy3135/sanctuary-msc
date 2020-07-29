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
using namespace std;
using namespace cv;
using namespace smsc_cvutil;

int main(int argc, char** argv)
{
	string path = "E:\\TestResources\\testPic1.png";
	string dir = "E:\\风景照片";
	smsc_cvutil::apply_filter2D_to_dir(dir);

//	cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}


