#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"

class SkinDetector
{
public:
	SkinDetector(void);

	void drawSkinColorSampler(cv::Mat input);
	void calibrate(cv::Mat input);
	cv::Mat getSkinMask(cv::Mat input);
private:
	int hLowThreshold = 0;
	int hHighThreshold = 0;
	int sLowThreshold = 0;
	int sHighThreshold = 0;
	int vLowThreshold = 0;
	int vHighThreshold = 0;

	bool calibrated = false;

	Rect skinColorSamplerRectangle1, skinColorSamplerRectangle2;

	void calculateThresholds(cv::Mat sample1, cv::Mat sample2);
	void performOpening(cv::Mat binaryImage, int structuralElementShapde, cv::Point structuralElementSize);
};