#pragma once
#include "mesh.hpp"
#include "scene.hpp"
#include "meshHolder.hpp"
#include "fogRenderer.hpp"
#include "jsonProperty.hpp"

class RemoveLocation {
public:
	Vector2D position;
	int layer;
};

class MeshScene : public Scene {
private:
	Mesh* mesh;	
	vector<Component*> scripts;
	vector<GameObject*> lights;
	vector<RemoveLocation> elementsToRemove;

public:
	MeshScene(string name, int tileSize): Scene(name) {
		createFog();
		mesh = new Mesh(tileSize);
		mesh->sceneName = name;
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
		elementsToRemove.clear();
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
		if (getAlpha()) {
			fog->onUpdate();
		}
		for (RemoveLocation l : elementsToRemove) {
			mesh->remove(l.position, l.layer);
		}
	}

	virtual void onUpdateAlpha() {
		if (!getAlpha()) {
			return;
		}
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

	void removeGameObject(Vector2D position, int layer) {
		elementsToRemove.push_back({ position, layer });
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

	Json serialize() {
		Json j = Json::object();
		j["name"] = getName();
		j["tiles"] = Json::array();
		for (pair<Vector2D, GameObject*> go : mesh->objects[(int)Layer::TILES]) {
			JsonProperty p = go.second->serialize();
			j["tiles"].push_back(p.value);
		}

		j["objects"] = Json::array();
		for (pair<Vector2D, GameObject*> go : mesh->objects[(int)Layer::OBJECTS]) {
			JsonProperty p = go.second->serialize();
			j["objects"].push_back(p.value);
		}

		j["entities"] = Json::array();
		for (pair<Vector2D, GameObject*> go : mesh->objects[(int)Layer::ENTITIES]) {
			JsonProperty p = go.second->serialize();
			j["entities"].push_back(p.value);
		}

		return j;
	}
};