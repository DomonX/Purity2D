#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
class Rotation {
private:
	double value;
public:
	Rotation() {
		this->value = 0;
	}
	Rotation(double angle) {
		this->value = angleToPi(angle);
	}
	double getAngle() {
		return value;
	}
	void setAngle(double angle) {
		value = angleToPi(angle);
	}
	Rotation operator+(double angle) {
		return Rotation(value + angleToPi(angle));
	}
	Rotation operator+(Rotation rotation) {
		return Rotation(piToAngle(getAngle() + rotation.getAngle()));
	}
	bool operator==(Rotation rotation) {
		return getAngle() == rotation.getAngle();
	}
private:
	double angleToPi(double angle) {
		return angle * M_PI / 180;
	}
	double piToAngle(double angle) {
		return angle * 180 / M_PI;
	}
};
