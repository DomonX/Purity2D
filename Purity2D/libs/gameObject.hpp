#pragma once

#include <vector>
#include "component.hpp"
using namespace std;
class GameObject : public Component {
private:
	vector<Component*> components;
	vector<GameObject*> children;
public:
	void addComponent(Component* component) {
		for (Component* i : components) {
			component->onGetOtherComponent(i);
			i->onGetOtherComponent(component);
		}
		for (GameObject* i : children) {
			i->onGetParentComponent(component);
		}
		components.push_back(component);
	}

	void addGameObject(GameObject* gameObject) {
		for (Component* i : components) {
			gameObject->onGetParentComponent(i);
		}
		children.push_back(gameObject);
	}

	void removeGameObject(GameObject* gameObject) {
		vector<GameObject*>::iterator iterator;
		for (vector<GameObject*>::iterator i = children.begin(); i != children.end(); i++) {
			if ((*i) == gameObject) {
				iterator = i;
				break;
			}
		}
		for (Component* component : components) {
			(*iterator)->onRemoveParentComponent(component);
		}
		children.erase(iterator);
	}

	void onGetParentComponent(Component* component) {
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