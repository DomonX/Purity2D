#pragma once

#include <vector>
#include "component.hpp"

class GameObject : Component {
private:
	std::vector<Component*> components;

public:
	void addComponent(Component* component) {
		for (Component* i : components) {
			component->onAddThisComponent(i);
			i->onAddOtherComponent(component);
		}
		components.push_back(component);
	}

	void onUpdate() {
		for (Component* i : components) {
			i->onUpdate();
		}
	}

	void onStart() {
		for (Component* i : components) {
			i->onStart();
		}
	}

	void onDelete() {
		for (Component* i : components) {
			free(i);
		}
	}
};