#pragma once

#include <map>

using namespace std;

class Color {
public:
	int r;
	int g;
	int b;
	Color(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	int evaluate() {
		return r * 256 * 256 + g * 256 + b;
	}
};

class DrawDecoder {
private:
	static DrawDecoder* instance;
	map<int, int> registry;
	DrawDecoder() {};
public:
	static DrawDecoder* get();
	void registerTile(Color color, int code) {
		registry[color.evaluate()] = code;
	}

	int getTile(Color color) {
		return registry[color.evaluate()];
	}
};