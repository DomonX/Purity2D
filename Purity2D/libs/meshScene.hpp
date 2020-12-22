#pragma once
#include "mesh.hpp"
#include "scene.hpp"

class MeshScene : public Scene {
private:
	Mesh* mesh;	
	vector<Component*> scripts;
	vector<GameObject*> lights;

public:
	MeshScene(string name, int tileSize): Scene(name) {
		createFog();
		mesh = new Mesh(tileSize);
	}

	void onStart() {
		camera->onStart();
		for (pair<Vector2D, map<int, GameObject*>> position : mesh->objects) {
			for (pair<int, GameObject*> layer: position.second) {
				layer.second->onStart();
			}
		}
		for (Component* script : scripts) {
			script->onStart();
		}
	}

	void onUpdate() {
		camera->onUpdate();
		Vector2D size = getSize();
		Vector2D pos = getPosition();
		Vector2D begin = (pos - (size / 2)).roundDown();
		Vector2D end = (pos + (size / 2)).round();
		for (int i = begin.getX(); i < end.getX(); i++) {
			for (int j = begin.getY(); j < end.getY(); j++) {
				for (pair<int, GameObject*> object : mesh->objects[Vector2D(i, j)]) {
					object.second->onUpdate();
				}
			}
		}
		for (GameObject* i : lights) {
			i->onUpdate();
		}
		for (Component* script : scripts) {
			script->onUpdate();
		}
		fog->onUpdate();
	}

	virtual void onUpdateAlpha() {
		for (GameObject* i : lights) {
			i->onUpdateAlpha();
		}
		fog->onUpdateAlpha();
	}

	Vector2D getPosition() {
		return (camera->getPosition() / mesh->getSize()).round();
	}

	Vector2D getSize() {
		return (camera->getSize() / mesh->getSize()).round();
	}

	virtual void createFog() {
		fog->addComponent(new FogRenderer());
		fog->addComponent(new Visibility());
		fog->addComponent(new Asset("fow3.png"));
		fog->addComponent(new Transform(camera->getSize(), camera->getSize() / 2, Rotation(0)));
		fog->onStart();
	}

	void addGameObject(GameObject* object, Vector2D position, int layer) {
		Transform* tr = object->getComponent<Transform>();
		(*tr) = Transform(tr->getScale() * mesh->getSize(), position * mesh->getSize(), Rotation());
		mesh->add(object, position, layer);
	}

	void addLight(GameObject* object) {
		lights.push_back(object);
	}

	void removeLight(GameObject* object) {
		vector<GameObject*>::iterator it = find(lights.begin(), lights.end(), object);
		if (it != lights.end()) {
			lights.erase(it);
			(*it)->onDelete();
			free(*it);
		}
	}

	void addScript(Component* script) {
		this->scripts.push_back(script);
	}
};