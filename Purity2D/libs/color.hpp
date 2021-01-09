#pragma once

#include <allegro5/allegro.h>

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

	Color(ALLEGRO_COLOR color) {
		unsigned char r, g, b;
		al_unmap_rgb(color, &r, &g, &b);
		this->r = r;
		this->g = g;
		this->b = b;
	}

	int evaluate(){
		return r * 256 * 256 + g * 256 + b;
	}
};