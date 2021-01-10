#pragma once

#include "vector2d.hpp"
#include "component.hpp"
#include "rotation.hpp"
#include "line.h"
//#include "gameState.hpp"

class Transform : public Component {
private:
	Vector2D scale;
	Vector2D position;
	Vector2D cachedPosition;
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

	void onRemoveParentComponent(Component* component) {
		Component::onRemoveParentComponent(component);
		removeIfIsInstance(&parentTransform, component);
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
		return position + (parentTransform != nullptr ? parentTransform->getPosition() : Vector2D::ZERO);
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

	Component* clone() {
		return new Transform(this);
	}

	void onStart() {
		cachedPosition = position + (parentTransform != nullptr ? parentTransform->getPosition() : Vector2D::ZERO);
	}

	bool isPointInside(Vector2D point) {
		vector<Line> lines = getLines();
		for (Line line : lines) {
			if (line.intersect(Line(Vector2D::ZERO, point))) {
				return true;
			}
		}
		return false;
	}

	bool isPointInsideQuick(Vector2D point) {
		Vector2D first = getPosition() - getScale() / 2;
		Vector2D second = getPosition() + getScale() / 2;
		return first.getX() < point.getX() &&
			first.getY() < point.getY() &&
			second.getX() > point.getX() &&
			second.getY() > point.getY();
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
