#pragma once

class Rotation {
private:
	double degrees;
public:
	Rotation();
	Rotation(double degrees);
	double getAngle();
	void setAngle(double angle);
	Rotation operator+(double angle) {
		return Rotation(degrees + angle);
	}
};
