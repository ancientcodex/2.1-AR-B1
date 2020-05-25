#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class handDetector
{
public:
	Mat detectHands(Mat input);
};

