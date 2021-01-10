#pragma once

#include <vector>
#include <algorithm>
#include "component.hpp"
using namespace std;
class GameObject : public Component {
private:
	int id;
	vector<Component*> components;
	vector<GameObject*> children;
	bool alreadyStarted;
public:
	GameObject(int id) : Component() {
		this->id = id;
		alreadyStarted = false;
	}

	void setScene(string name) {
		Component::setScene(name);
		for (Component* i : components) {
			i->setScene(name);
		}
	}

	void addComponent(Component* component) {
		component->getGameObject(this);
		component->setScene(getScene());
		for (Component* i : components) {
			component->onGetOtherComponent(i);
			i->onGetOtherComponent(component);
		}
		for (GameObject* i : children) {
			i->onGetParentComponent(component);
		}
		components.push_back(component);
		if (alreadyStarted) {
			component->onStart();
		}
	}

	void addGameObject(GameObject* gameObject) {
		gameObject->setScene(getScene());
		for (Component* i : components) {
			gameObject->onGetParentComponent(i);
		}
		children.push_back(gameObject);
		if (alreadyStarted) {
			gameObject->onStart();
		}
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

	void onUpdateAlpha() {
		for (Component* i : components) {
			i->onUpdateAlpha();
		}
	}

	void onStart() {
		for (Component* i : components) {
			i->onStart();
		}
		alreadyStarted = true;
	}

	void onDelete() {
		for (Component* i : components) {
			i->onDelete();
		}
		for (Component* i : components) {
			delete(i);
		}
		components.clear();
	}

	GameObject* clone() {
		GameObject* o = new GameObject(id);
		for (Component* component : components) {
			o->addComponent(component->clone());
		}
		for (GameObject* gameObject : children) {
			o->addGameObject(gameObject->clone());
		}
		return o;
	}

	Component* getComponent(bool(*comparator)(Component*)) {
		for (Component* component : components) {
			if (comparator(component)) {
				return component;
			}
		}
		return nullptr;
	}

	template<class T> T* getComponent() {
		T* temp = nullptr;
		for (Component* component : components) {
			temp = dynamic_cast<T*>(component);
			if (temp) {
				return temp;
			}
		}
		return temp;
	}

	JsonProperty serialize() {
		JsonProperty data = JsonProperty();
		data.created = true;
		data.value = Json::object();
		data.value["id"] = id;

		vector<JsonProperty> props;
		for (Component* component : components) {
			props.push_back(component->serialize());
		}

		remove_if(props.begin(), props.end(), [](JsonProperty p) { return !p.created; });

		for (JsonProperty p : props) {
			data.value["data"][p.name] = p.value;
		}

		return data;
	}

};