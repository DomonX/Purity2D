#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

#include "vector2d.hpp"

class Transform {
private:
    Vector2D scale;
    Vector2D position;
public:
    Transform(Vector2D scale, Vector2D position) {
        this->scale = scale;
        this->position = position;
    }
    static const Transform base;

    Vector2D getScale() {
        return scale;
    }

    Vector2D getPosition() {
        return position;
    }

    Transform operator*(Vector2D scale) {
        return Transform(getScale() + scale, getPosition());
    }

    Transform operator+(Vector2D vec) {
        return Transform(getScale(), getPosition() + vec);
    }

    Vector2D getLeftUp() {
        return getPosition() - ( getScale() / 2 );
    }

    Vector2D getLeftDown() {
		return getPosition() 
			- getScale() / 2 * VectorOrientation::HORIZONTAL
			+ getScale() / 2 * VectorOrientation::VERTICAL;
    }

    Vector2D getRightUp() {
		return getPosition()
			+ getScale() / 2 * VectorOrientation::HORIZONTAL
			- getScale() / 2 * VectorOrientation::VERTICAL;
    }

    Vector2D getRightDown() {
		return getPosition() + (getScale() / 2);
    }
};

#endif // RECTANGLE_HPP_INCLUDED
