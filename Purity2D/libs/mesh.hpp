#pragma once

#include <map>
#include "gameObject.hpp"
#include "vector2d.hpp"

class Mesh {
private:
	vector<GameObject*> lights;
	int tileSize;
public:
	map<Vector2D, map<int, GameObject*>> objects;

	Mesh(int tileSize) {
		this->tileSize = tileSize;
	}

	void add(GameObject* object, Vector2D position, int layer) {
		objects[position][layer] = object;
	}

	int move(GameObject* object, Vector2D from, Vector2D to, int layer) {
		objects[from].erase(layer);
		if (objects[from].size() == 0) {
			objects.erase(from);
		}

		while(objects[to][layer] != nullptr) {
			layer++;
		}

		objects[to][layer] = object;
		return layer;
	}

	Vector2D calculatePosition(Vector2D scale, Vector2D position) {
		return position * tileSize + scale;
	}

	void remove(Vector2D position, int layer) {
		objects[position][layer]->onDelete();
		objects[position].erase(layer);
	}

	int getSize() {
		return tileSize;
	}
};