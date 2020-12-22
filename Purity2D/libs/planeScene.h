#pragma once

#include "scene.hpp"
#include "fogRenderer.hpp"
#include "gameObject.hpp"

using namespace std;
class PlaneScene : public Scene {
private:
	vector<GameObject*> objects;
	vector<GameObject*> lights;
public:
	PlaneScene(string name) : Scene(name) { 
		createFog();
	}

	void onStart() {
		camera->onStart();
		for (GameObject* i : objects) {
			i->onStart();
		}
	}

	void onUpdate() {
		camera->onUpdate();
		for (GameObject* i : objects) {
			i->onUpdate();
		}
		for (GameObject* i : lights) {
			i->onUpdate();
		}
		fog->onUpdate();
	}

	virtual void onUpdateAlpha() {
		for (GameObject* i : lights) {
			i->onUpdateAlpha();
		}
		fog->onUpdateAlpha();
	}

	void onDelete() {
		camera->onDelete();
		if (fog) {
			fog->onDelete();
		}
	}

	void addGameObject(GameObject* object) {
		objects.push_back(object);
	}

	void addLight(GameObject* object) {
		lights.push_back(object);
	}

	void removeGameObject(GameObject* object) {
		vector<GameObject*>::iterator it = find(objects.begin(), objects.end(), object);
		if (it != objects.end()) {
			objects.erase(it);
			(*it)->onDelete();
			free(*it);
		}
	}

	void removeLight(GameObject* object) {
		vector<GameObject*>::iterator it = find(lights.begin(), lights.end(), object);
		if (it != lights.end()) {
			lights.erase(it);
			(*it)->onDelete();
			free(*it);
		}
	}

protected:
	virtual void createFog() {
		fog->addComponent(new FogRenderer());
		fog->addComponent(new Visibility());
		fog->addComponent(new Asset("fow3.png"));
		fog->addComponent(new Transform(camera->getSize(), camera->getSize() / 2, Rotation(0)));
		fog->onStart();
	}
};