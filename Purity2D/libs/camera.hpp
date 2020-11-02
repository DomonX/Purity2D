#pragma once

#include "gameObject.hpp"
#include "transform.hpp"
class Camera : public GameObject {
	Transform* cameraPosition;
	Camera() {
		cameraPosition = new Transform(Vector2D::ZERO, Vector2D::ZERO, Rotation(0));
		addComponent(cameraPosition);
	}
};
