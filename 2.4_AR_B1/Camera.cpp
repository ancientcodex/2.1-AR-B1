#include "Camera.h"

	VideoCapture cap;
	Camera::Camera(int cameraNum)
	{
		cv::VideoCapture temp(cameraNum);
		cap = temp;
	}

	int Camera::StartCapture(Mat *frame) 
	{
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

		while (1)
		{
			bool bSuccess = cap.read(*frame);

			if (!bSuccess)
			{
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}

			imshow("MyVideo", *frame);

			if (waitKey(1) == 27)
			{
				cout << "esc key is pressed by user" << endl;
				break;
			}
		}
		return 0;
	}
