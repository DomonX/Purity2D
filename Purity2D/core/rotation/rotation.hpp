#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
class Rotation {
private:
	double value;
public:
	Rotation();
	Rotation(double degrees);
	double getAngle();
	void setAngle(double angle);
	Rotation operator+(double angle);
	Rotation operator+(Rotation rotation);
private:
	double angleToPi(double angle);
	double piToAngle(double pi);
};
