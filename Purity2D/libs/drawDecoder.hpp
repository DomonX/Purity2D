#pragma once

#include <map>

#include "objectFactory.hpp"
#include "color.hpp"

using namespace std;

class DrawDecoder {
private:
	static DrawDecoder* instance;
	map<Layer, map<int, int>> registry;
	DrawDecoder() {};
public:
	static DrawDecoder* get();
	void regist(int code, Layer layer, Color color) {
		registry[layer][color.evaluate()] = code;
	}

	void regist(int code, Color color, Layer layer, CreationFunction func, ObjectType type) {
		registry[layer][color.evaluate()] = code;
		ObjectFactory::get()->regist(code, layer, func, type);
	}

	int getTile(Color color, Layer layer) {
		return registry[layer][color.evaluate()];
	}
};