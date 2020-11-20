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
    long double x, y;
    void setX(long double x) {
        this->x = x;
    }
    void setY(long double y) {
        this->y = y;
    }
public:
    static const Vector2D UP;
    static const Vector2D DOWN;
    static const Vector2D LEFT;
    static const Vector2D RIGHT;
	static const Vector2D ZERO;

    Vector2D() {
        setX(0);
        setY(0);
    }

    Vector2D(long double x, long double y) {
        setX(x);
        setY(y);
    }

    long double getX() {
        return x;
    }

    long double getY() {
        return y;
    }

    Vector2D operator+(Vector2D vec) {
        return Vector2D(getX() + vec.getX(), getY() + vec.getY());
    }

	Vector2D operator-(Vector2D vec) {
		return Vector2D(getX() - vec.getX(), getY() - vec.getY());
	}

    Vector2D operator*(long double scale) {
        return Vector2D(getX() * scale, getY() * scale);
    }

	Vector2D operator/(long double scale) {
		return Vector2D(getX() / scale, getY() / scale);
	}

    Vector2D operator*(VectorOrientation orientation) {
        if(orientation == VERTICAL) {
            return Vector2D(0, getY());
        }
        if(orientation == HORIZONTAL) {
            return Vector2D(getX(), 0);
        }
    }

	Vector2D operator*(Rotation rotation) {
		return Vector2D(
			x * cos(rotation.getAngle()) - y * sin(rotation.getAngle()),
			y * cos(rotation.getAngle()) + x * sin(rotation.getAngle())
		);
	}

	bool operator==(Vector2D vec) {
		return getX() == vec.getX() && getY() == vec.getY();
	}

	Vector2D absolute() {
		return Vector2D(x < 0 ? x * -1 : x, y < 0 ? y * -1 : y);
	}

    string toString() {
        stringstream ss;
        ss << "(" << setprecision(20) << getX() << ", " << getY() << ")";
        return ss.str();
    }
};

