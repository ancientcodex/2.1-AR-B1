#pragma once
#include <queue>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"

class DataManager
{
	std::queue<std::tuple<std::string, cv::Point>> stream;
public:
	void addPoint(std::string hand, cv::Point p);
	std::tuple<std::string, cv::Point> getPoint();
	void clearBuffer();
};

