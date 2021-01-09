#pragma once

#include "gameObject.hpp"
#include "scene.hpp"
#include "vector2d.hpp"
#include "objectCreator.hpp"
#include <map>

using namespace std;

class ObjectFactory {
private:
	static ObjectFactory* instance;
	map<Layer, map<int, ObjectCreator*>> registry;
	ObjectFactory() {}
public:

	static ObjectFactory* get();

	void regist(int code, ObjectCreator* obj) {
		this->registry[obj->getLayer()][code]= obj;
	}

	Json compile(int code, Layer layer, CreationData params) {
		return registry[layer][code]->compile(params);
	}

	GameObject* load(int code, Layer layer, LoadData params) {
		return registry[layer][code]->load(params);	
	}

	ObjectType type(int code, Layer layer) {
		ObjectCreator* cr = registry[layer][code];
		if (!cr) {
			return ObjectType::UNKNOWN;
		}
		return cr->getType();
	}
};