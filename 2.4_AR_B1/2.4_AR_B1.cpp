
// shows camera vision.
// Do not forget to add libs for this project in linker

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

//test

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// Do not forget to change camera if you have multiple
	VideoCapture cap(0);

	// Camera check
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	// Checks screen size
	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	// Window frame to show live camera screen
	namedWindow("MyVideo", WINDOW_AUTOSIZE);

	// Continue loop get the frames for 
	Mat frame;

	while (1)
	{
		bool bSuccess = cap.read(frame);

		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		imshow("MyVideo", frame);

		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}