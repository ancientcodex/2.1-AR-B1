#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/types.hpp>



class handDetector
{
public:
	cv::Mat detectHands(cv::Mat input);
	cv::Point getCenter();
};

