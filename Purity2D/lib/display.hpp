#pragma once

#include <allegro5/allegro.h>

class Display {
public:
	Display();

	void setResolution(unsigned int width, unsigned int height);
	void stop();
private:
	ALLEGRO_DISPLAY * display = NULL;
	ALLEGRO_MONITOR_INFO monitor;
};