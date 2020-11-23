#pragma once

#include "gameObject.hpp"
#include "transform.hpp"
#include "collider.hpp"

class Camera : public GameObject {
private:
	Transform* cameraPosition;
	Collider* collider;
public:
	/*!
		\brief Creates Camera with components: Transform and Collider
	*/
	Camera() {
		cameraPosition = new Transform(Vector2D(355, 200), Vector2D(0, 0), Rotation(0));
		collider = new Collider();
		addComponent(cameraPosition);
		addComponent(collider);
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

	/*!
		\brief Checks if transform is visible in camera
		\param transform Transform which is checked if is visible by camera
	*/
	bool isVisible(Transform* transform) {
		Vector2D cameraVec = (getSize() / 2).absolute();
		Vector2D transformVec = transform->getScale().absolute();
		double hor = (cameraVec * VectorOrientation::HORIZONTAL + transformVec * VectorOrientation::HORIZONTAL).len();
		double ver = (cameraVec * VectorOrientation::VERTICAL + transformVec * VectorOrientation::VERTICAL).len();
		Vector2D connVec = Line(getPosition(), transform->getPosition()).toVector().absolute();
		double connHor = (connVec * VectorOrientation::HORIZONTAL).len();
		double connVer = (connVec * VectorOrientation::VERTICAL).len();
		return hor > connHor && ver > connVer;
	}

	virtual GameObject* clone() {
		return this;
	}
};

