#pragma once

#include <string>
#include <vector>
#include <algorithm>
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

public:
	/*!	\brief Constructor of scene with given name \warning Name should be unique	*/
	Scene(string name) {
		this->name = name;
		camera = new Camera();
		screen = al_get_target_bitmap();
		fog = new GameObject();
	}

	/*!	\brief Returns name of Scene */
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
		fog->onUpdate();
		for (GameObject* i : lights) {
			i->onUpdateAlpha();
		}
		fog->onUpdateAlpha();
	}

	/*!	\brief Lifecycle hook called when Scene is destroyed */
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

	/*!	\brief Add Light to Scene \see GameObject	*/
	void addLight(GameObject* object) {
		objects.push_back(object);
		lights.push_back(object);
	}

	/*!	\brief Remove GameObject from Scene \see GameObject	*/
	void removeGameObject(GameObject* object) {
		vector<GameObject*>::iterator it = find(objects.begin(), objects.end(), object);
		if (it != objects.end()) {
			objects.erase(it);
			(*it)->onDelete();
			free(*it);
		}
	}

	/*!	\brief Remove Light from Scene \see GameObject	*/
	void removeLight(GameObject* object) {
		vector<GameObject*>::iterator itl = find(lights.begin(), lights.end(), object);
		vector<GameObject*>::iterator ito = find(objects.begin(), objects.end(), object);
		if (itl != lights.end()) {
			objects.erase(itl);
		}
		if (ito != objects.end()) {
			objects.erase(ito);
			(*ito)->onDelete();
			free(*ito);
		}
	}

	/*!	\brief Returns Camera of Scene \see Camera	*/
	Camera * getCamera() {
		return camera;
	}

	/*! \brief Creates fog on the Scene \see FogRenderer */
	void createFog(GameObject* fog) {
		this->fog->onDelete();
		free(this->fog);
		this->fog = fog;
		this->fog->addComponent(new Transform(camera->getSize(), camera->getSize() / 2, Rotation(0)));
		this->fog->onStart();
	}

};