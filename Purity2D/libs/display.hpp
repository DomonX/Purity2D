#pragma once

#include <allegro5/allegro.h>
#include <vector>

#include "line.h"

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
	/*! 
		\brief Getter method for Display singleton
		\returns Global Display element
	*/
	static Display* get();
	/*!
		\brief Assigns new resolution to display
		\param width new width of display
		\param height new height of display
	*/
	void setResolution(unsigned int width, unsigned int height);
	/*!
		\brief Stops working of display
		\warning Shouldnt be called directly
	*/
	void onStop();
	/*!
		\brief Returns size of display
		\returns Vector of display size
	*/

	void fullscreen(bool mode);
	Vector2D getSize() {
		return size;
	}
};