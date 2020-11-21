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
	Transform* parentTransform = nullptr;
public:
	Transform(Vector2D scale, Vector2D position, Rotation rotation) {
		this->scale = scale;
		this->position = position;
		this->rotation = rotation;
		lines = vector<Line>();
	}

	Transform(Transform* transform) {
		this->scale = transform->scale;
		this->position = transform->position;
		this->rotation = transform->rotation;
		lines = vector<Line>();
	}

	void onGetParentComponent(Component* component) {
		Component::onGetParentComponent(component);
		storeIfIsInstance(&parentTransform, component);
	}

	Transform operator*(Vector2D scale) {
		return Transform(getScale() + scale, getPosition(), getRotation());
	}

	Transform operator+(Vector2D vec) {
		return Transform(getScale(), getPosition() + vec, getRotation());
	}

	Transform operator+(Rotation rot) {
		return Transform(getScale(), getPosition(), getRotation() + rot);
	}

	bool operator==(Transform trans) {
		return trans.getScale() == getScale() && trans.getPosition() == getPosition() && trans.getRotation() == getRotation();
	}

	bool operator!=(Transform trans) {
		return !(*this == trans);
	}

	Vector2D getScale() {
		return scale;
	}

	Vector2D getPosition() {
		return parentTransform != nullptr ? parentTransform->getPosition() + position : position;
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
		if (lines.size() == 0) {
			calculateLines();
		}
		return lines;
	}

	string toString() {
		return "{ Pos: " + this->getPosition().toString() + ", Scale: " + this->getScale().toString() + ", Rotation: " + this->getRotation().toString() + " }";
	}

private:
	Vector2D rotateVector(Vector2D vector) {
		return getPosition() + vector * rotation;
	}

	void calculateLines() {
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
