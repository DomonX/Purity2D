#pragma once

#include "gameObject.hpp"
#include "scene.hpp"
#include "vector2d.hpp"
#include <map>

using namespace std;


enum class ObjectType {UNKNOWN, WALL, FLOOR, PLAYER};
enum class Layer {TILES, OBJECTS, ENTITIES, SCRIPTS};

class CreationData {
public:
	int id;
	Scene* scene;
	Vector2D position;
	void* extra;

	CreationData(int id, Scene* scene, Vector2D position, void* extra) {
		this->id = id;
		this->scene = scene;
		this->position = position;
		this->extra = extra;
	}
};

typedef GameObject* (*CreationFunction)(CreationData);

class ObjectData {
public:
	CreationFunction fun;
	ObjectType type;
};

class ObjectFactory {
private:
	static ObjectFactory* instance;
	map<Layer, map<int, ObjectData>> creations;
	ObjectFactory() {}
public:

	static ObjectFactory* get();

	void regist(int code, Layer layer, CreationFunction func, ObjectType type) {
		this->creations[layer][code].fun = func;
		this->creations[layer][code].type = type;
	}

	GameObject* create(int code, Layer layer, CreationData params) {
		CreationFunction fun = creations[layer][code].fun;
		if (fun == nullptr) {
			return nullptr;
		}
		return fun(params);
	}

	ObjectType type(int code, Layer layer) {
		return creations[layer][code].type;
	}
};