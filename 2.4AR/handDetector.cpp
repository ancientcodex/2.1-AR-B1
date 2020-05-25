#include "handDetector.h"
vector<vector<Point>> contours;
int findBiggestContour(int filter = -2);

Mat handDetector::detectHands(Mat input)
{
	vector<Vec4i> hierarchy;
	Mat src_gray, threshold_output, drawing;
	if (input.empty())
		return drawing;

	// we work only on the 1 channel result, since this function is called inside a loop we are not sure that this is always the case
	if (input.channels() != 1)
		return drawing;


	blur(input, src_gray, Size(3, 3));

	threshold(src_gray, threshold_output, 100, 255, THRESH_BINARY);
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	/// Find the convex hull object for each contour
	vector<vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}
	// Draw contours + hull results TODO: remove this if debug is no longer required
	drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	int biggestContour = findBiggestContour();
	Scalar color = Scalar(255, 255, 255);
	drawContours(drawing, contours, biggestContour, color, 1, 8, vector<Vec4i>(), 0, Point());
	drawContours(drawing, hull, biggestContour, color, 1, 8, vector<Vec4i>(), 0, Point());

	contours.clear();
	return drawing;
}

int findBiggestContour(int filter) {
	// find the biggest contour (let's suppose it's our hand)
	int biggest_contour_index = -1;
	double biggest_area = 0.0;

	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i], false);
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


