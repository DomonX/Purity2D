#pragma once

#include "vector2d.hpp"
#include "component.hpp"
#include "rotation.hpp"
#include "line.h"

class Transform : public Component {
private:
	Vector2D scale;
	Vector2D position;
	Rotation rotation;
	vector<Line> lines;
public:
	Transform(Vector2D scale, Vector2D position, Rotation rotation) {
		this->scale = scale;
		this->position = position;
		this->rotation = rotation;
		lines = vector<Line>();
		calculateLines();
	}

	static const Transform base;

	Transform operator*(Vector2D scale) {
		return Transform(getScale() + scale, getPosition(), getRotation());
	}

	Transform operator+(Vector2D vec) {
		return Transform(getScale(), getPosition() + vec, getRotation());
	}

	Transform operator+(Rotation rot) {
		return Transform(getScale(), getPosition(), getRotation() + rot);
	}

	Vector2D getScale() {
		return scale;
	}

	Vector2D getPosition() {
		return position;
	}

	Rotation getRotation() {
		return rotation;
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

	vector<Line> getLines() {
		return lines;
	}

private:
	Vector2D rotateVector(Vector2D vector) {
		return getPosition() + vector * rotation;
	}

	void calculateLines() {
		lines.clear();
		Vector2D rightDown = getRightDown();
		Vector2D rightUp = getRightUp();
		Vector2D leftDown = getLeftDown();
		Vector2D leftUp = getLeftUp();
		lines.push_back(Line(rightDown, rightUp));
		lines.push_back(Line(leftUp, rightUp));
		lines.push_back(Line(rightDown, leftDown));
		lines.push_back(Line(leftDown, leftUp));
	}
};
