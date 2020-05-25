#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"


class BackgroundRemover {
public:
	BackgroundRemover(void);
	void calibrate(cv::Mat input);
	cv::Mat getForeground(cv::Mat input);

private:
	cv::Mat background;
	bool calibrated = false;

	cv::Mat getForegroundMask(cv::Mat input);
	void removeBackground(cv::Mat input, cv::Mat background);
};