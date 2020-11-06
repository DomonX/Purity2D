#pragma once

#include <allegro5/allegro.h>

#include <allegro5/allegro.h>
#include "line.h"
#include <vector>
class Display {
private:
	ALLEGRO_DISPLAY* display = NULL;
	static Display* instance;
	vector<Vector2D> screens = vector<Vector2D>();
	Vector2D size;
	unsigned char currentAdapter;
	unsigned int currentMode;
	void createScreen();
	Display();
public:
	static Display* get();
	void setResolution(unsigned int width, unsigned int height);
	void stop();
	Vector2D getSize() {
		return size;
	}
};