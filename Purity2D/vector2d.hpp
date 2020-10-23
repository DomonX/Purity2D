#ifndef VECTOR2D_HPP_INCLUDED
#define VECTOR2D_HPP_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

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
    static const Vector2D RIGHT_UP;
    static const Vector2D RIGHT_DOWN;
    static const Vector2D LEFT_UP;
    static const Vector2D LEFT_DOWN;

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

    Vector2D operator*(long double scale) {
        return Vector2D(getX() * scale, getY() * scale);
    }

    Vector2D operator*(VectorOrientation orientation) {
        if(orientation == VERTICAL) {
            return Vector2D(0, getY());
        }

        if(orientation == HORIZONTAL) {
            return Vector2D(getX(), 0);
        }
    }

    string toString() {
        stringstream ss;
        ss << "(" << setprecision(20) << getX() << ", " << getY() << ")";
        return ss.str();
    }
};

#endif // VECTOR2D_HPP_INCLUDED
