#include "BackgroundRemover.h"

BackgroundRemover::BackgroundRemover(void) {
	background;
	calibrated = false;
}

void BackgroundRemover::calibrate(cv::Mat input) {
	cvtColor(input, background, cv::COLOR_BGR2GRAY);
	calibrated = true;
}

cv::Mat BackgroundRemover::getForeground(cv::Mat input) {
	cv::Mat foregroundMask = getForegroundMask(input);
	//imshow("foregroundMask", foregroundMask);
	cv::Mat foreground;
	input.copyTo(foreground, foregroundMask);
	return foreground;
}

cv::Mat BackgroundRemover::getForegroundMask(cv::Mat input) {
	cv::Mat foregroundMask;

	if (!calibrated) {
		foregroundMask = cv::Mat::zeros(input.size(), CV_8UC1);
		return foregroundMask;
	}
	cvtColor(input, foregroundMask, cv::COLOR_BGR2GRAY);
	removeBackground(foregroundMask, background);
	return foregroundMask;
}

void BackgroundRemover::removeBackground(cv::Mat input, cv::Mat background) {
	int thresholdOffset = 10;

	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols; j++) {
			uchar framePixel = input.at<uchar>(i, j);
			uchar bgPixel = background.at<uchar>(i, j);

			if (framePixel >= bgPixel - thresholdOffset && framePixel <= bgPixel + thresholdOffset)
				input.at<uchar>(i, j) = 0;
			else
				input.at<uchar>(i, j) = 255;
		}
	}
}