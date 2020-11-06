#pragma once

#include <string>
#include <vector>
#include "gameObject.hpp"
#include "camera.hpp"

using namespace std;
class Scene {
private:
	string name;
	vector<GameObject*> objects;
	Camera* camera;
public:
	Scene(string name) {
		this->name = name;
		camera = new Camera();
	}

	string getName() {
		return name;
	}

	void onStart() {
		for (GameObject* i : objects) {
			i->onStart();
		}
	}

	void onUpdate() {
		for (GameObject* i : objects) {
			i->onUpdate();
		}
	}

	void onDelete() {
		for (GameObject* i : objects) {
			i->onDelete();
		}
	}

	void addGameObject(GameObject * object) {
		objects.push_back(object);
	}

	void removeGameObject(GameObject* object) {
		for (GameObject* i : objects) {
			if (i == object) {
				i->onDelete();
				free(i);
			}
		}
	}

	Camera * getCamera() {
		return camera;
	}
};