#pragma once
#include "component.hpp"
#include "transform.hpp"
#include <allegro5/allegro_primitives.h>
class Collider : public Component {
private:
	Transform* transform = nullptr;
public:
	/*!
		@copydoc Component::onGetOtherComponent(Component*)
		\warning There should be Transform component connected to the same GameObject
		\see Transform
	*/
	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}

	/*!
		\brief Checks if GameObject collides with a Line by its Transform
		\param line Line to check if it collides with GameObject
		\sa Line Transform Collider::collides(Transform)
	*/
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

	/*!
		\brief Checks if GameObject collides with a Transform by its Transform
		\param transform Transform to check if it collides with GameObject
		\sa Transform Collider::collides(Line)
	*/
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

	/*!
		\brief Checks if one transform is inside of second one
		\param inner Transform to check if its inside
		\param outer Transform to check if have second inside
		\todo Should be extracted to service
		\sa Line Transform Collider::collides(Line) Collider::collides(Transform)
	*/
	bool isInside(Transform inner, Transform outer) {
		vector<Line> lines = outer.getLines();
		Line positionLine = Line(outer.getPosition(), inner.getPosition());
		for (Line i : lines) {
			if (i.intersect(positionLine)) {
				return false;
			}
		}
		return true;
	}

	/*!	@copydoc Component::clone()	*/
	Component* clone() {
		return new Collider();
	}
};