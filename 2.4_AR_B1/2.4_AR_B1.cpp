
// shows camera vision.
// Do not forget to add libs for this project in linker

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "Camera.h"

//test

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Camera cam(1);
	Mat frame;
	cam.StartCapture(&frame);
	return 0;
}