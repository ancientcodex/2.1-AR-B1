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


class VisionManager
{
	cv::VideoCapture cam;
	DataManager dataManager;

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
	VisionManager(DataManager* dManager);
	void updater();
};
