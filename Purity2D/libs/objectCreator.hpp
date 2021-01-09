#pragma once

#include "jsonProperty.hpp"
#include "gameObject.hpp"
#include "scene.hpp"

enum class ObjectType { UNKNOWN, WALL, FLOOR, PLAYER };
enum class Layer { TILES, OBJECTS, ENTITIES, SCRIPTS };

class LoadData {
public:
	Scene* scene;
	Json loadedData;
};

class CreationData {
public:
	int id;
	Vector2D position;
	void* extra;

	CreationData(int id, Vector2D position, void* extra) {
		this->id = id;
		this->position = position;
		this->extra = extra;
	}
};

class ObjectCreator {
private:
	ObjectType type;
	Layer layer;
public:

	ObjectCreator(ObjectType type, Layer layer) {
		this->type = type;
		this->layer = layer;
	}

	virtual Json compile(CreationData data) {
		return Json::object();
	}

	virtual GameObject* load(LoadData data) {
		return nullptr;
	}

	ObjectType getType() {
		return type;
	}

	Layer getLayer() {
		return layer;
	}
};