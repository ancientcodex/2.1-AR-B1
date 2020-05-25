#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "3D.h"
#include "BackgroundRemover.h"
#include "SkinDetector.h"
#include "FaceDetector.h"
#include "FingerCount.h"
#include "handDetector.h"

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

bool calibrated = false;

double factor = 0.6;

void facerecognition();

int main(int argc, char* argv[])
{
	//thread t1(startup);
	thread t2(facerecognition);
	//t1.join();
	t2.join();
	return 0;
}

void facerecognition() {

	VideoCapture cam("http://192.168.1.27:4747/mjpegfeed?640x480");
	cam.set(CAP_PROP_SETTINGS, 1);

	if (!cam.isOpened()) {
		cout << "Can't find camera!" << endl;
		return;
	}

	Mat frame, frameOut, handMask, foreground, handleft, handright;

	BackgroundRemover backgroundRemover;
	SkinDetector skinDetector;
	FaceDetector faceDetector;
	handDetector handDetector;

	int i = 0;
	while (true) {
		cam >> frame;
		resize(frame, frame, Size(), factor, factor, INTER_AREA);
		frameOut = frame.clone();

		if (!calibrated)
			skinDetector.drawSkinColorSampler(frameOut);

		if (i % 5 == 0) {
			foreground = backgroundRemover.getForeground(frame);
			faceDetector.removeFaces(frame, foreground);
			handMask = skinDetector.getSkinMask(foreground);
		}

		Mat handmaskL(handMask, Rect(0, 0, handMask.rows * factor, handMask.cols * factor));
		Mat handmaskR(handMask, Rect(handMask.rows * factor, 0, handMask.rows * factor, handMask.cols * factor));

		handleft = handDetector.detectHands(handmaskL);
		handright = handDetector.detectHands(handmaskR);

		imshow("foreground", foreground);
		imshow("handMask", handMask);
		imshow("output", frameOut);

		imshow("handleft", handleft);
		imshow("handright", handright);





		int key = waitKey(1);
		if (key == 27) // esc
			break;
		else if (key == 115) {// s
			backgroundRemover.calibrate(frame);
			skinDetector.calibrate(frame);
			calibrated = true;
		}
		i++;
	}
}