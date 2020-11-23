#pragma once

#include <vector>
#include "component.hpp"
using namespace std;
class GameObject : public Component {
private:
	vector<Component*> components;
	vector<GameObject*> children;
public:
	/*!
		\brief Adds Component do GameObject
		\param component Component to add
		\see Component
	*/
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

	/*!
		\brief Adds child GameObject
		\param gameObject GameObject to add
	*/
	void addGameObject(GameObject* gameObject) {
		for (Component* i : components) {
			gameObject->onGetParentComponent(i);
		}
		children.push_back(gameObject);
	}

	/*!
		\brief Removes child GameObject
		\param gameObject GameObject to remove
	*/
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

	/*!
		@copydoc Component::onGetParentComponent(Component*)
		\see Component
	*/
	void onGetParentComponent(Component* component) {
		for (Component* i : components) {
			i->onGetParentComponent(component);
		}
	}

	/*!
		@copydoc Component::onUpdate(Component*)
		\see Component
	*/
	void onUpdate() {
		for (Component* i : components) {
			i->onUpdate();
		}
	}

	/*!
		@copydoc Component::onStart(Component*)
		\see Component
	*/
	void onStart() {
		for (Component* i : components) {
			i->onStart();
		}
	}

	/*!
		@copydoc Component::onDelete(Component*)
		\see Component
	*/
	void onDelete() {
		for (Component* i : components) {
			free(i);
		}
	}

	GameObject* clone() {
		GameObject* o = new GameObject();
		for (Component* component : components) {
			o->addComponent(component->clone());
		}
		for (GameObject* gameObject : children) {
			o->addGameObject(gameObject->clone());
		}
		return o;
	}

};