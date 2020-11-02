#pragma once
#include "component.hpp"
#include "transform.hpp"
class Collider : public Component {
private:
	Transform* transform = nullptr;

public:

	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}


	bool collides(Line line) {
		if (this->transform == nullptr) {
			return false;
		}
		vector<Line> lines = this->transform->getLines();
		for (Line i : lines) {
			if (line.intersect(i)) {
				return true;
			}
		}
	}

	bool collides(Transform transform) {
		if (this->transform == nullptr) {
			return false;
		}
		vector<Line> lines = transform.getLines();
		for (Line i : lines) {
			if (collides(i)) {
				return true;
			}
		}
		if (isInside(*this->transform, transform)) {
			return true;
		}
		if (isInside(transform, *this->transform)) {
			return true;
		}
		return false;
	}

	bool isInside(Transform inner, Transform outer) {
		vector<Line> lines = outer.getLines();
		Line positionLine = Line(Vector2D::ZERO, inner.getPosition());
		int collisionCount = 0;
		for (Line i : lines) {
			if (i.intersect(positionLine)) {
				collisionCount++;
			}
		}
		return collisionCount % 2 == 1;
	}
};