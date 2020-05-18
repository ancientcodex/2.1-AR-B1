#include "VissionTools.h"

#define w 400

void VissionTools::addCircle(Mat img, Point center)
{
	circle(img,
		center,
		w / 32,
		Scalar(0, 0, 255),
		FILLED,
		LINE_8);
}
