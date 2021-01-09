#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "jsonProperty.hpp"
#include "gameObject.hpp"
#include "camera.hpp"
#include "asset.hpp"
#include "sagaElement.h"

using namespace std;
class Scene : public SagaElement {
protected:
	string name;
	Camera* camera;
	GameObject* fog;
	GameObject* player;
	bool hasAlpha = false;
public:
	Scene(string name) {
		this->name = name;
		camera = createCamera();
		createFog();
	}

	string getName() {
		return name;
	}

	Camera * getCamera() {
		return camera;
	}

	GameObject** getPlayer() {
		return &player;
	}

	void setPlayer(GameObject* player) {
		this->player = player;
	}

	virtual Json serialize() {
		return Json::object();
	}

	void setAlpha(bool mode) {
		hasAlpha = mode;
	}

	bool getAlpha() {
		return hasAlpha;
	}

protected:
	virtual Camera* createCamera() {
		return new Camera();
	}
	virtual void createFog() {
		this->fog = new GameObject(0);
	}
};