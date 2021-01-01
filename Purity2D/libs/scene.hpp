#pragma once

#include <string>
#include <vector>
#include <algorithm>
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

protected:
	virtual Camera* createCamera() {
		return new Camera();
	}
	virtual void createFog() {
		this->fog = new GameObject();
	}
};