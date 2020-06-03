#include "DataManager.h"

void DataManager::addPoint(std::string hand,cv::Point p)
{
	std::tuple<std::string, cv::Point> t { hand, p };
	stream.push(t);
}

std::tuple<std::string, cv::Point> DataManager::getPoint()
{
	std::tuple<std::string, cv::Point> t;
	if (stream.empty())
		return t;
	t = stream.front();
	stream.pop();
	return t;
}

