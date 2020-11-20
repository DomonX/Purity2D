#pragma once

#include <vector>
#include "component.hpp"
using namespace std;
class GameObject : public Component {
private:
	vector<Component*> components;
public:
	void addComponent(Component* component) {
		for (Component* i : components) {
			component->onGetOtherComponent(i);
			i->onGetOtherComponent(component);
		}
		components.push_back(component);
	}

	void onGetOtherComponent(Component* component) {
		for (Component* i : components) {
			i->onGetParentComponent(component);
		}
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