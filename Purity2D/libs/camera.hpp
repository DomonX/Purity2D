#pragma once

#include "gameObject.hpp"
#include "transform.hpp"

class Camera : public GameObject {
private:
	Transform* cameraPosition;
	Vector2D pos;
public:
	/*!
		\brief Creates Camera with components: Transform and Collider
	*/
	Camera() {
		cameraPosition = new Transform(Vector2D(1920 / 6, 1080 / 6), Vector2D(0, 0), Rotation(0));
		addComponent(cameraPosition);
	}

	/*!
		\brief Returns size of camera
		\returns Size of camera as Vector
	*/
	Vector2D getSize() {
		return cameraPosition->getScale();
	}

	/*!
		\brief Returns position of camera
		\returns Posotion of camera as Vector
	*/
	Vector2D getPosition() {
		return cameraPosition->getPosition();
	}

	/*!
		\brief Moves camera by target Vector
		\param vec Vector by which camera will be moved
	*/
	void move(Vector2D vec) {
		(*cameraPosition) = (*cameraPosition) + vec;
	}

	void resize(Vector2D vec) {
		(*cameraPosition) = Transform(vec, getPosition(), Rotation(0));
	}

	/*!
		\brief Checks if transform is visible in camera
		\param transform Transform which is checked if is visible by camera
	*/
	bool isVisible(Transform* transform) {
		Vector2D cameraVec = (getSize() / 2).absolute();
		Vector2D transformVec = transform->getScale().absolute();
		double hor = ((cameraVec + transformVec) * VectorOrientation::HORIZONTAL).lenQ();
		double ver = ((cameraVec + transformVec) * VectorOrientation::VERTICAL).lenQ();
		Vector2D connVec = Line(pos, transform->getPosition()).toVector().absolute();
		double connHor = (connVec * VectorOrientation::HORIZONTAL).lenQ();
		double connVer = (connVec * VectorOrientation::VERTICAL).lenQ();
		return hor > connHor && ver > connVer;
	}

	/*!	@copydoc Component::onUpdate()	*/
	void onUpdate() {
		this->pos = getPosition();
	}

	/*!	@copydoc Component::clone()	*/
	virtual GameObject* clone() {
		return this;
	}
};

