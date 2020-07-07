#include "cv_util.h";
#include <opencv2/highgui.hpp>
#include <iostream>
int main(int argc, char** argv)
{
	smsc_cvutil::open_photo_with_highgui("E:\\TestResources\\testPic1.png");
	cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}
