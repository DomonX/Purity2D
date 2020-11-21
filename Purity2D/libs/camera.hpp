#pragma once

#include "gameObject.hpp"
#include "transform.hpp"
#include "collider.hpp"

class Camera : public GameObject {
private:
	Transform* cameraPosition;
	Collider* collider;
public:
	Camera() {
		cameraPosition = new Transform(Vector2D(1920, 1080), Vector2D(0, 0), Rotation(0));
		collider = new Collider();
		addComponent(cameraPosition);
		addComponent(collider);
	}

	Vector2D getSize() {
		return cameraPosition->getScale();
	}

	Vector2D getPosition() {
		return cameraPosition->getPosition();
	}

	void move(Vector2D vec) {
		(*cameraPosition) = (*cameraPosition) + vec;
	}

	bool isVisible(Transform* transform) {
		return collider->collides(transform);
	}
};

