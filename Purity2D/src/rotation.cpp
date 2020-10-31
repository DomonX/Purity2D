#include "../lib/rotation.hpp"

double Rotation::getAngle()
{
	return degrees;
}

void Rotation::setAngle(double angle) {
	degrees = angle;
}

Rotation::Rotation(double angle) {
	this->degrees = angle;
}

Rotation::Rotation() {
	this->degrees = 0;
}
