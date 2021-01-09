#pragma once

#include "component.hpp"
#include "mouse.hpp"
#include "vector2d.hpp"
#include "mouseElement.hpp"

class Button : public Component {
private:
	Transform* transform;
	MouseElement* mouseElement;	
public:

	Button() {
		mouseElement = new MouseElement();
	}

	void setScene(string sceneName) {
		mouseElement->setScene(sceneName);
	}

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&transform, component);
	}

	void onStart() {
		mouseElement->onStart();
		mouseElement->connectTransform(transform);
		mouseElement->connectOwner(this);
	}

	void onDelete() {
		mouseElement->onDelete();
		delete(mouseElement);
	}

	MouseElement* mouse() {
		return mouseElement;
	}

};