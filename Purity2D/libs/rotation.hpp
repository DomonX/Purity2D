#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring>
using namespace std;
class Rotation {
private:
	double value;
public:
	/*!	\brief Constructor of Zero Rotation	*/
	Rotation() {
		this->value = 0;
	}
	/*!	\brief Constructor of Rotation with given angle */
	Rotation(double angle) {
		this->value = angleToPi(angle);
	}
	/*!	\brief Returns angle of Rotation in Pi	*/
	double getAngle() {
		return value;
	}
	/*!	\brief Sets angle of Rotation in degrees	*/
	void setAngle(double angle) {
		value = angleToPi(angle);
	}
	/*!	\brief Adds angle to rotation in degrees	*/
	Rotation operator+(double angle) {
		return Rotation(value + angleToPi(angle));
	}
	/*!	\brief Adds two Rotations	*/
	Rotation operator+(Rotation rotation) {
		return Rotation(piToAngle(getAngle() + rotation.getAngle()));
	}
	/*!	\brief Compares two Rotations	*/
	bool operator==(Rotation rotation) {
		return getAngle() == rotation.getAngle();
	}
	/*!	\brief Multiply Rotation	*/
	Rotation operator*(double value) {
		return Rotation(piToAngle(getAngle()) * value);
	}
	/*!	\brief Stringifies Rotation	*/
	string toString() {
		return to_string(getAngle());
	}
private:
	double angleToPi(double angle) {
		return angle * M_PI / 180;
	}
	double piToAngle(double angle) {
		return angle * 180 / M_PI;
	}
};
