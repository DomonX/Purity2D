#pragma once

#include "mouseObserver.hpp"
#include "transform.hpp"
#include "mouse.hpp"
#include "transformScaler.hpp"

typedef void (*MouseFunction)();
typedef void (*ClickFunction)(Component* current, ClickType click);

class MouseElement : public MouseObserver, public SceneElement {
private:
	bool isHovered = false;
	bool wasClicked = false;
	Transform* transform;
	Component* owner;
public:
	MouseFunction onHover = []() {};
	MouseFunction onBlur = []() {};
	MouseFunction onAxis = []() {};
	ClickFunction onClick = [](Component* current, ClickType click) {};
	MouseFunction onRelease = []() {};

	void onStart() {
		Mouse::get()->subscribe(this);
	}

	void connectTransform(Transform* tr) {
		transform = tr;
	}

	void connectOwner(Component* component) {
		this->owner = component;
	}

	void mouseClick(ClickType click) {
		if (isHovered) {
			wasClicked = true;
			onClick(owner, click);
		}
	}

	void mouseRelease() {
		if (wasClicked) {
			wasClicked = false;
			onRelease();
		}
	}

	void mouseMove(Vector2D pos) {
		if (!transform) {
			return;
		}

		if (isHovered) {
			checkIfExits(pos);
		}
		else {
			checkIfEnters(pos);
		}
	}

	void onDelete() {
		Mouse::get()->unsubscribe(this);
	}
private:
	void checkIfExits(Vector2D pos) {
		if (isPointInside(pos)) {
			onAxis();
		}
		else {
			cout << "entered" << endl;
			isHovered = false;
			onBlur();
		}
	}

	void checkIfEnters(Vector2D pos) {
		if (isPointInside(pos)) {
			cout << "exited" << endl;
			onHover();
			isHovered = true;
		}
		else {
			onAxis();
		}
	}

	bool isPointInside(Vector2D pos) {
		Vector2D point = TransformScaler().scaleVector(pos);
		return transform->isPointInsideQuick(point);
	}


};