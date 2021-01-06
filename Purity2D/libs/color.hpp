#pragma once

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

	int evaluate(){
		return r * 256 * 256 + g * 256 + b;
	}
};