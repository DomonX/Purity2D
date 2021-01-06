#pragma once
#include "mesh.hpp"
#include "scene.hpp"
#include "meshHolder.hpp"

class MeshScene : public Scene {
private:
	Mesh* mesh;	
	vector<Component*> scripts;
	vector<GameObject*> lights;
	GameObject* player;

public:
	MeshScene(string name, int tileSize): Scene(name) {
		createFog();
		mesh = new Mesh(tileSize);
	}

	void onStart() {
		camera->onStart();
		for (pair<int, map<Vector2D, GameObject*>> layer : mesh->objects) {
			for (pair<Vector2D, GameObject*> object : layer.second) {
				object.second->onStart();
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
		for (pair<int, map<Vector2D, GameObject*>> layer : mesh->objects) {
			for (int i = begin.getX(); i < end.getX(); i++) {
				for (int j = begin.getY(); j < end.getY(); j++) {
					GameObject* obj = layer.second[Vector2D(i, j)];
					if (obj) {
						obj->onUpdate();
					}
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
		object->addComponent(new MeshHolder(&mesh, position, layer));
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

	Vector2D calculatePosition(Vector2D position) {
		return this->mesh->calculatePosition(position);
	}

	GameObject** getPlayer() {
		return &player;
	}

	void setPlayer(GameObject* player) {
		this->player = player;
	}
};