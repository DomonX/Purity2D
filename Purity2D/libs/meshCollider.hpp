#pragma once

#include "component.hpp"
#include "meshHolder.hpp"


enum CollisionSettings { IN_DOWN, IN_UP, IN_LEFT, IN_RIGHT, OUT_DOWN, OUT_UP, OUT_LEFT, OUT_RIGHT };

struct Colliders {
	bool colliders[8];
};

class MeshCollider : public Component {

	Colliders collisions;
	MeshHolder* mesh = nullptr;

public:

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&mesh, component);
	}

	MeshCollider(Colliders collisions) {
		this->collisions = collisions;
	}

	bool collidesIn(Vector2D position) {
		Vector2D objectPosition = mesh->getPosition();
		if (objectPosition.getX() < position.getX()) {
			return collisions.colliders[IN_RIGHT];
		}
		if (objectPosition.getX() > position.getX()) {
			return collisions.colliders[IN_LEFT];
		}
		if (objectPosition.getY() > position.getY()) {
			return collisions.colliders[IN_DOWN];
		}
		if (objectPosition.getY() < position.getY()) {
			return collisions.colliders[IN_UP];
		}
	}

	bool collidesOut(Vector2D destination) {
		Vector2D objectPosition = mesh->getPosition();
		if (objectPosition.getX() < destination.getX()) {
			return collisions.colliders[OUT_RIGHT];
		}
		if (objectPosition.getX() > destination.getX()) {
			return collisions.colliders[OUT_LEFT];
		}
		if (objectPosition.getY() > destination.getY()) {
			return collisions.colliders[OUT_DOWN];
		}
		if (objectPosition.getY() < destination.getY()) {
			return collisions.colliders[OUT_UP];
		}
	}
};