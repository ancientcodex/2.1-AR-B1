#include "handDetector.h"

std::vector<std::vector<cv::Point>> contours;
int findBiggestContour(int filter = -2);

cv::Mat handDetector::detectHands(cv::Mat input)
{
	std::vector<cv::Vec4i> hierarchy;
	cv::Mat src_gray, threshold_output, drawing;
	if (input.empty())
		return drawing;

	// we work only on the 1 channel result, since this function is called inside a loop we are not sure that this is always the case
	if (input.channels() != 1)
		return drawing;

	contours.clear();

	cv::blur(input, src_gray, cv::Size(3, 3));

	cv::threshold(src_gray, threshold_output, 100, 255, cv::THRESH_BINARY);
	cv::findContours(threshold_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	/// Find the convex hull object for each contour
	std::vector<std::vector<cv::Point> >hull(contours.size());
	//foreach
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(cv::Mat(contours[i]), hull[i], false);
	}
	// Draw contours + hull results TODO: remove this if debug is no longer required
	drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
	int biggestContour = findBiggestContour();
	cv::Scalar color = cv::Scalar(255, 255, 255);
	drawContours(drawing, contours, biggestContour, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
	drawContours(drawing, hull, biggestContour, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());

	return drawing;
}

int findBiggestContour(int filter) {
	// find the biggest contour (let's suppose it's our hand)
	int biggest_contour_index = -1;
	double biggest_area = 0.0;

	for (int i = 0; i < contours.size(); i++) {
		double area = cv::contourArea(contours[i], false);
		if (area > biggest_area) {
			if (biggest_contour_index != filter) {
				//cout << "passed" << endl;
				biggest_area = area;
				biggest_contour_index = i;
			}
		}
	}
	return biggest_contour_index;
}

cv::Point handDetector::getCenter() {
	cv::Point c;
	//check if contours is not empty
	if (contours.size() <= 0) {
		return c;
	}
	//get moments from contours.
	std::vector<cv::Moments> m(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		m[i] = moments(contours[i], false);
	}
	//compute center using the moments.
	std::vector<cv::Point> center(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		center[i] = cv::Point(m[i].m10 / m[i].m00, m[i].m01 / m[i].m00);
	}
	int contour = findBiggestContour();
	c = center[contour];

	return c;
}


