#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <string>

#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"
#include "handDetector.h"

#include <iostream>
#include "DataManager.h"


class VisionManager
{
	cv::VideoCapture cam;
	std::shared_ptr<DataManager> dataManager;

	bool calibrated = false;
	double factor = 0.6;
	cv::Point HandL;
	cv::Point HandR;

	cv::Mat frame, frameOut, handMask, foreground, handleft, handright;

	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	handDetector handDetector;
public:
	VisionManager(std::shared_ptr<DataManager> dManager);
	void updater();
};
