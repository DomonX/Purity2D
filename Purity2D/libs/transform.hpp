#pragma once

#include "vector2d.hpp"
#include "component.hpp"
#include "rotation.hpp"
#include "line.h"

class Transform : public Component {
private:
	int layer;
	Vector2D scale;
	Vector2D position;
	Rotation rotation;
	vector<Line> lines;
	Transform* parentTransform = nullptr;
public:
	/*!	\brief Construct transform on default layer	*/
	Transform(Vector2D scale, Vector2D position, Rotation rotation) {
		this->scale = scale;
		this->position = position;
		this->rotation = rotation;
		this->layer = 0;
		lines = vector<Line>();
	}

	/*!	\brief Construct transform on given layer */
	Transform(Vector2D scale, Vector2D position, Rotation rotation, int layer) {
		this->scale = scale;
		this->position = position;
		this->rotation = rotation;
		this->layer = layer;
		lines = vector<Line>();
	}

	/*!	\brief Copies Transform	*/
	Transform(Transform* transform) {
		this->scale = transform->scale;
		this->position = transform->position;
		this->rotation = transform->rotation;
		lines = vector<Line>();
	}

	/*!
		@copydoc Component::onGetParentComponent(Component*)
		\brief Trasnsform is subsribing for any Transform in Parent GameObject
	*/
	void onGetParentComponent(Component* component) {
		Component::onGetParentComponent(component);
		storeIfIsInstance(&parentTransform, component);
	}

	/*!
		@copydoc Component::onRemoveParentComponent(Component*)
		\brief Trasnsform is removing Parent GameObject if neccesary
	*/
	void onRemoveParentComponent(Component* component) {
		Component::onRemoveParentComponent(component);
		removeIfIsInstance(&parentTransform, component);
	}

	/*!	\brief Scales transform	*/
	Transform operator*(Vector2D scale) {
		return Transform(getScale() + scale, getPosition(), getRotation());
	}

	/*!	\brief Moves Transform	*/
	Transform operator+(Vector2D vec) {
		return Transform(getScale(), getPosition() + vec, getRotation());
	}

	/*!	\brief Rotates Transform	*/
	Transform operator+(Rotation rot) {
		return Transform(getScale(), getPosition(), getRotation() + rot);
	}

	/*!	\brief Compares two Transforms	*/
	bool operator==(Transform trans) {
		return trans.getScale() == getScale() && trans.getPosition() == getPosition() && trans.getRotation() == getRotation();
	}

	/*!	\brief Negated Comparision of two transforms */
	bool operator!=(Transform trans) {
		return !(*this == trans);
	}

	/*!	\brief Returns size of Transform */
	Vector2D getScale() {
		return scale;
	}

	/*!	\brief Returns position on Transform */
	Vector2D getPosition() {
		return position + (parentTransform != nullptr ? parentTransform->getPosition() : Vector2D::ZERO);
	}

	/*!	\brief Returns Rotation of Transform */
	Rotation getRotation() {
		return rotation;
	}

	/*!	\brief Returns Vector to LeftUp Corner \warning Doesnt include Rotation	*/
	Vector2D getLeftUp() {
		return rotateVector(getScale() / 2 * -1);
	}

	/*!	\brief Returns Vector to LeftDown Corner \warning Doesnt include Rotation	*/
	Vector2D getLeftDown() {
		return rotateVector(getScale() / 2 * VectorOrientation::VERTICAL - getScale() / 2 * VectorOrientation::HORIZONTAL);
	}

	/*!	\brief Returns Vector to RightUp Corner \warning Doesnt include Rotation	*/
	Vector2D getRightUp() {
		return rotateVector(getScale() / 2 * VectorOrientation::HORIZONTAL - getScale() / 2 * VectorOrientation::VERTICAL);
	}

	/*!	\brief Returns Vector to RightDown Corner \warning Doesnt include Rotation	*/
	Vector2D getRightDown() {
		return rotateVector(getScale() / 2);
	}

	/*!	\brief Returns Lines building Transform	*/
	vector<Line> getLines() {
		if (lines.size() == 0) {
			calculateLines();
		}
		return lines;
	}

	/*!	\brief Returns Layer of Transform */
	int getLayer() {
		return layer;
	}

	/*!	\brief Changes Layer of Transform */
	Transform setLayer(int layer) {
		return Transform(getScale(), getPosition(), getRotation(), layer);
	}

	/*!	\brief Stringifies Transform */
	string toString() {
		return "{ Pos: " + this->getPosition().toString() + ", Scale: " + this->getScale().toString() + ", Rotation: " + this->getRotation().toString() + " }";
	}

	Component* clone() {
		return new Transform(this);
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
