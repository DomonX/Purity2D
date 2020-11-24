#pragma once

#include <string>
#include <vector>
#include "gameObject.hpp"
#include "camera.hpp"
#include "asset.hpp"

using namespace std;
class Scene {
private:
	string name;
	vector<GameObject*> objects;
	vector<GameObject*> lights;
	Camera* camera;
	GameObject* fog;
	ALLEGRO_BITMAP* screen;

	ALLEGRO_BITMAP* alphaChannel;
	Vector2D alphaSize;

public:
	/*!	\brief Constructor of scene with given name \warning Name should be unique	*/
	Scene(string name) {
		this->name = name;
		camera = new Camera();
		screen = al_get_target_bitmap();
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
		camera->onUpdate();
		for (GameObject* i : objects) {
			i->onUpdate();
		}
		for (GameObject* i : lights) {
			i->onUpdate();
		}
		fog->onUpdate();
	}

	/*!	\brief Lifecycle hook called when Scene is destroyed	*/
	void onDelete() {
		camera->onDelete();
		for (GameObject* i : objects) {
			i->onDelete();
		}
		if (fog) {
			fog->onDelete();
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

	/*!	\brief Add Light to Scene \see GameObject	*/
	void addLight(GameObject* object) {
		lights.push_back(object);
	}

	/*!	\brief Remove Light from Scene \see GameObject	*/
	void removeLight(GameObject* object) {
		for (GameObject* i : lights) {
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

	/*! \brief Creates fog on the Scene \see FogRenderer */
	void createFog(GameObject* fog) {
		this->fog = fog;
		this->fog->addComponent(new Transform(camera->getSize(), camera->getSize() / 2, Rotation(0)));
		this->fog->onStart();
	}
	


};