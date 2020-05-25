#pragma once
#include <opencv2/opencv.hpp>


class FingerCount {
	public:
		FingerCount(void);
		cv::Mat findFingersCount(cv::Mat input_image, cv::Mat frame);
	
	private:
		cv::Scalar color_blue;
		cv::Scalar color_green;
		cv::Scalar color_red;
		cv::Scalar color_black;
		cv::Scalar color_white;
		cv::Scalar color_yellow;
		cv::Scalar color_purple;
		double findPointsDistance(cv::Point a, cv::Point b);
		std::vector<cv::Point> compactOnNeighborhoodMedian(std::vector<cv::Point> points, double max_neighbor_distance);
		double findAngle(cv::Point a, cv::Point b, cv::Point c);
		bool isFinger(cv::Point a, cv::Point b, cv::Point c, double limit_angle_inf, double limit_angle_sup, cv::Point palm_center, double distance_from_palm_tollerance);
		std::vector<cv::Point> findClosestOnX(std::vector<cv::Point> points, cv::Point pivot);
		double findPointsDistanceOnX(cv::Point a, cv::Point b);
		void drawVectorPoints(cv::Mat image, std::vector<cv::Point> points, cv::Scalar color, bool with_numbers);
};