#pragma once

#include <opencv2/opencv.hpp>


class FaceDetector {
	public:
		FaceDetector(void);
		void removeFaces(cv::Mat input, cv::Mat output);
};