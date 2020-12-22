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

    Vector2D() {
		this->x = 0;
		this->y = 0;
    }

    Vector2D(double x, double y) {
		this->x = x;
		this->y = y;
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

    Vector2D operator*(double scale) {
        return Vector2D(getX() * scale, getY() * scale);
    }

	double operator*(Vector2D vec) {
		return getX() * vec.getX() + getY() * vec.getY();
	}

	Vector2D operator/(double scale) {
		return Vector2D(getX() / scale, getY() / scale);
	}

	Vector2D operator/(Vector2D vec) {
		return Vector2D(getX() / vec.getX(), getY() / vec.getY());
	}

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

	bool operator<(const Vector2D& v) const {
		if (v.y > y) {
			return true;
		} else if (v.y == y && v.x > x) {
			return true;
		} else {
			return false;
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

	Vector2D round() {
		return Vector2D((int)getX() + 1, (int)getY() + 1);
	}

	Vector2D roundDown() {
		return Vector2D((int)getX() - 1, (int)getY() - 1);
	}

	double len() {
		return sqrt(lenQ());
	}

	double lenQ() {
		double x = getX();
		double y = getY();
		return(y * y + x * x);
	}

    string toString() {
        stringstream ss;
        ss << "(" << setprecision(20) << getX() << ", " << getY() << ")";
        return ss.str();
    }
};

