#ifndef Camera_H
#define Camera_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

#pragma once
class Camera
{
public:
	Camera(int cameraNum);
	int StartCapture(Mat* frame);

};

#endif