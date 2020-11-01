#include "display.hpp"

Display::Display() {
	al_get_monitor_info(1, &monitor);
	display = al_create_display(monitor.x2 - monitor.x1 + 1, monitor.y2 - monitor.y1 + 1);
	al_set_display_flag(display, ALLEGRO_WINDOWED, true);
}

void Display::setResolution(unsigned int width, unsigned int height) {
	al_resize_display(display, width, height);
}

void Display::stop() {
	if (display != nullptr) {
		al_destroy_display(display);
	}
}
