#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

#include "vector2d.hpp"
#include "component.hpp"
#include "rotation.hpp"

class Transform : public Component {
private:
    Vector2D scale;
    Vector2D position;
	Rotation rotation;
public:
    Transform(Vector2D scale, Vector2D position, Rotation rotation) {
        this->scale = scale;
        this->position = position;
		this->rotation = rotation;
    }
    static const Transform base;

    Vector2D getScale() {
        return scale;
    }

    Vector2D getPosition() {
		return position;
    }

	Rotation getRotation() {
		return rotation;
	}

    Transform operator*(Vector2D scale) {
        return Transform(getScale() + scale, getPosition(), getRotation());
    }

    Transform operator+(Vector2D vec) {
        return Transform(getScale(), getPosition() + vec, getRotation());
    }

	Transform operator+(Rotation rot) {
		return Transform(getScale(), getPosition(), getRotation() + rot.getAngle());
	}

    Vector2D getLeftUp() {
		return rotateVector(getScale() / 2 * -1);
    }

    Vector2D getLeftDown() {
		return rotateVector(getScale() / 2 * VectorOrientation::VERTICAL - getScale() / 2 * VectorOrientation::HORIZONTAL);
    }

    Vector2D getRightUp() {
		return rotateVector(getScale() / 2 * VectorOrientation::HORIZONTAL - getScale() / 2 * VectorOrientation::VERTICAL);
    }

    Vector2D getRightDown() {
		return rotateVector(getScale() / 2);
    }
private: 
	Vector2D rotateVector(Vector2D vector) {
		return getPosition() + vector * rotation;
	}
};

#endif // RECTANGLE_HPP_INCLUDED
