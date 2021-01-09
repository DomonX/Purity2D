#pragma once

#include <map>
#include "gameObject.hpp"
#include "vector2d.hpp"

class Mesh : public SceneElement {
private:
	vector<GameObject*> lights;
	int tileSize;
public:
	string sceneName;
	map<int, map<Vector2D, GameObject*>> objects;

	Mesh(int tileSize) {
		this->tileSize = tileSize;
	}

	void add(GameObject* object, Vector2D position, int layer) {
		object->setScene(sceneName);
		objects[layer][position] = object;
	}

	int move(GameObject* object, Vector2D from, Vector2D to, int layer) {
		objects[layer].erase(from);
		objects[layer][to] = object;
		return layer;
	}

	Vector2D calculatePosition(Vector2D position) {
		return position * tileSize;
	}

	void remove(Vector2D position, int layer) {
		objects[layer][position]->onDelete();
		objects[layer].erase(position);
	}

	int getSize() {
		return tileSize;
	}

	vector<GameObject*> getObjectsInPosition(Vector2D pos) {
		vector<GameObject*> objectsInPosition;
		for ( pair<int, map<Vector2D, GameObject*>> layer : objects) {
			GameObject* go = layer.second[pos];
			if (go) {
				objectsInPosition.push_back(go);
			}
		}
		return objectsInPosition;
	}
};