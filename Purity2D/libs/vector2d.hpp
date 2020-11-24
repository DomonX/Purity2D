#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "rotation.hpp"

using namespace std;

enum VectorOrientation { VERTICAL, HORIZONTAL };

class Vector2D {
private:
    double x, y;
public:
    static Vector2D UP;
    static Vector2D DOWN;
    static Vector2D LEFT;
    static Vector2D RIGHT;
	static Vector2D ZERO;

	/*!		\brief Constructs Zero vector	*/
    Vector2D() {
		this->x = 0;
		this->y = 0;
    }

	/*!		\brief Constructs vector to point (x,y)	*/
    Vector2D(double x, double y) {
		this->x = x;
		this->y = y;
    }

	/*!		\returns X position of vector	*/
    long double getX() {
        return x;
    }

	/*!		\returns Y position of vector	*/
    long double getY() {
        return y;
    }

	/*!		\brief Adds two vectors	*/
    Vector2D operator+(Vector2D vec) {
        return Vector2D(getX() + vec.getX(), getY() + vec.getY());
    }

	/*!		\brief Subtracts two vectors	*/
	Vector2D operator-(Vector2D vec) {
		return Vector2D(getX() - vec.getX(), getY() - vec.getY());
	}

	/*!		\brief Multiply two vectors	*/
    Vector2D operator*(double scale) {
        return Vector2D(getX() * scale, getY() * scale);
    }

	/*!		\brief Divide two vectors	*/
	Vector2D operator/(double scale) {
		return Vector2D(getX() / scale, getY() / scale);
	}

	/*!		\brief Returns Vertical or Horizontal part of vector	*/
    Vector2D operator*(VectorOrientation orientation) {
        if(orientation == VERTICAL) {
            return Vector2D(0, getY());
        }
        if(orientation == HORIZONTAL) {
            return Vector2D(getX(), 0);
        }
    }

	bool operator>(Vector2D vec) {
		int x1 = vec.getX();
		int x2 = getX();
		int y1 = vec.getY();
		int y2 = getY();
		return x1 * x1 + y1 * y1 > x2* x2 + y2 * y2;
	}

	/*!		\brief Rotates Vector	*/
	Vector2D operator*(Rotation rotation) {
		return Vector2D(
			x * cos(rotation.getAngle()) - y * sin(rotation.getAngle()),
			y * cos(rotation.getAngle()) + x * sin(rotation.getAngle())
		);
	}

	/*!		\brief Compares two vectors	*/
	bool operator==(Vector2D vec) {
		return getX() == vec.getX() && getY() == vec.getY();
	}

	/*!		\brief Returns absolute value of vector (changes minus to plus values)	*/
	Vector2D absolute() {
		return Vector2D(x < 0 ? x * -1 : x, y < 0 ? y * -1 : y);
	}

	double len() {
		double x = getX();
		double y = getY();
		return sqrt(y * y + x * x);
	}

	double lenQ() {
		double x = getX();
		double y = getY();
		return(y * y + x * x);
	}

	/*!	\brief Stringify vector	*/
    string toString() {
        stringstream ss;
        ss << "(" << setprecision(20) << getX() << ", " << getY() << ")";
        return ss.str();
    }
};

