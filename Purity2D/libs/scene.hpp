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
	/*!	\brief Constructor of scene with given name \warning Name should be unique	*/
	Scene(string name) {
		this->name = name;
		camera = new Camera();
	}

	/*!	\brief Returns name of Scene	*/
	string getName() {
		return name;
	}

	/*!	\brief Lifecycle hook called when Game is Started or Scene is added to game	*/
	void onStart() {
		camera->onStart();
		for (GameObject* i : objects) {
			i->onStart();
		}
	}

	/*!	\brief Lifecycle hook called when frame is rendered	*/
	void onUpdate() {
		for (GameObject* i : objects) {
			i->onUpdate();
		}
	}

	/*!	\brief Lifecycle hook called when Scene is destroyed	*/
	void onDelete() {
		for (GameObject* i : objects) {
			i->onDelete();
		}
	}

	/*!	\brief Add GameObject to Scene \see GameObject	*/
	void addGameObject(GameObject * object) {
		objects.push_back(object);
	}

	/*!	\brief Remove GameObject from Scene \see GameObject	*/
	void removeGameObject(GameObject* object) {
		for (GameObject* i : objects) {
			if (i == object) {
				i->onDelete();
				free(i);
			}
		}
	}

	/*!	\brief Returns Camera of Scene \see Camera	*/
	Camera * getCamera() {
		return camera;
	}
};