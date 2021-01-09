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

	void regist(int code, Color color, ObjectCreator* c) {
		registry[c->getLayer()][color.evaluate()] = code;
		ObjectFactory::get()->regist(code, c);
	}

	int getTile(Color color, Layer layer) {
		return registry[layer][color.evaluate()];
	}
};