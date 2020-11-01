#include "rotation.hpp"

double Rotation::getAngle() {
	return value;
}

void Rotation::setAngle(double angle) {
	value = angleToPi(angle);
}

Rotation::Rotation(double angle) {
	this->value = angleToPi(angle);
}

Rotation::Rotation() {
	this->value = 0;
}

Rotation Rotation::operator+(double angle) {
	return Rotation(value + angleToPi(angle));
}

Rotation Rotation::operator+(Rotation rotation) {
	return Rotation(piToAngle(getAngle() + rotation.getAngle()));
}

double Rotation::angleToPi(double angle) {
	return angle * M_PI / 180;
}

double Rotation::piToAngle(double angle) {
	return angle * 180 / M_PI;
}
