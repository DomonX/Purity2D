#pragma once

#include <vector>

#include "sagaElement.h"
#include "jsonProperty.hpp"

class Component : public SagaElement {
public:
	virtual void onGetOtherComponent(Component* component) {}
	virtual void onRemoveOtherComponent(Component component) {}
	virtual void onGetParentComponent(Component* component) {}
	virtual void onRemoveParentComponent(Component* component) {}
	virtual void getGameObject(Component* gameObject) {}
	virtual JsonProperty serialize() { return JsonProperty(); }
	virtual Component* clone() { return nullptr; }

protected:
	template<class T> void storeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = t;
		}
	}

	template<class T> void removeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = nullptr;
		}
	}
};