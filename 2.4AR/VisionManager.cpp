#include "VisionManager.h"

VisionManager::VisionManager() {

	cam = cv::VideoCapture("http://192.168.1.28:4747/mjpegfeed?640x480");
	cam.set(cv::CAP_PROP_SETTINGS, 1);

	if (!cam.isOpened()) {
		std::cout << "Can't find camera!" << std::endl;
		return;
	}
}

void VisionManager::updater() {
	int i = 0;

	while (true) {
		cam >> frame;
		cv::resize(frame, frame, cv::Size(), factor, factor, cv::INTER_AREA);
		frameOut = frame.clone();

		if (!calibrated)
			skinDetector.drawSkinColorSampler(frameOut);
		//not required to do every turn of the loop
		if (i % 5 == 0) {
			foreground = backgroundRemover.getForeground(frame);
			faceDetector.removeFaces(frame, foreground);
			handMask = skinDetector.getSkinMask(foreground);
		}

		// split frame in 2 sides
		cv::Mat handmaskL(handMask, cv::Rect(0, 0, handMask.rows * factor, handMask.cols * factor));
		cv::Mat handmaskR(handMask, cv::Rect(handMask.rows * factor, 0, handMask.rows * factor, handMask.cols * factor));

		//Left Hand
		handleft = handDetector.detectHands(handmaskL);
		HandL = handDetector.getCenter();
		std::cout << "center: x: " << HandL.x << " y: " << HandL.y << std::endl;

		//Right Hand
		handright = handDetector.detectHands(handmaskR);
		HandR = handDetector.getCenter();
		std::cout << "center: x: " << HandR.x << " y: " << HandR.y << std::endl;

		cv::imshow("foreground", foreground);
		cv::imshow("handMask", handMask);
		cv::imshow("output", frameOut);

		cv::imshow("handleft", handleft);
		cv::imshow("handright", handright);

		int key = cv::waitKey(1);
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