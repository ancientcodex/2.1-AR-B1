#include "DataManager.h"
#include <mutex>

std::mutex mtx;

void DataManager::addPoint(std::string hand,cv::Point p)
{
	mtx.lock();
	std::tuple<std::string, cv::Point> t { hand, p };
	stream.push(t);
	mtx.unlock();
}

std::tuple<std::string, cv::Point> DataManager::getPoint()
{
	mtx.lock();
	std::tuple<std::string, cv::Point> t;
	if (stream.empty()) {
		mtx.unlock();
		return t;
	}
	t = stream.front();
	stream.pop();
	mtx.unlock();
	return t;
}

