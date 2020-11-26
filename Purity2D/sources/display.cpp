#include "../libs/display.hpp"

Display* Display::instance = nullptr;

Display* Display::get() {
	if (instance == nullptr) {
		instance = new Display();
	}
	return instance;
}

void Display::createScreen() {
	al_set_new_display_adapter(currentAdapter);
	Vector2D mainScreen = screens.at(currentAdapter);
	//int height = mainScreen.getY();
	//int width = mainScreen.getX();
	int height = 900;
	int width = 1600;
	size = Vector2D(width, height);
	if (display != nullptr) {
		al_destroy_display(display);
	}
	display = al_create_display(size.getX(), size.getY());
	al_set_display_flag(display, currentMode, true);
}

Display::Display() {
	ALLEGRO_MONITOR_INFO monitor;
	int screensNumber = al_get_num_video_adapters();
	for (int i = 0; i < screensNumber; i++) {
		al_get_monitor_info(i, &monitor);
		screens.push_back(Vector2D(monitor.x1, monitor.y2).absolute());
	}
	currentAdapter = 0;
	currentMode = ALLEGRO_WINDOWED;
	createScreen();
}


void Display::setResolution(unsigned int width, unsigned int height) {
	size = Vector2D(width, height);
	al_resize_display(display, width, height);
}

void Display::onStop() {
	if (display != nullptr) {
		al_destroy_display(display);
	}
}

void Display::fullscreen(bool mode) {
	int curr = mode ? ALLEGRO_FULLSCREEN_WINDOW : ALLEGRO_WINDOWED;
	int bef = mode ? ALLEGRO_WINDOWED : ALLEGRO_FULLSCREEN_WINDOW;
	currentMode = curr;
	al_set_display_flag(display, curr, true);
	al_set_display_flag(display, bef, false);
	if (mode) {
		windowedSize = size / 2;
		size = screens.at(currentAdapter);
	}
	else {
		size = windowedSize;
	}
}

void Display::presentRendering(bool mode) {
	if (mode && cachedPresentationSize == Vector2D::ZERO) {
		cachedPresentationSize = size;
		size = size / 2;
	}
	if (!mode && !(cachedPresentationSize == Vector2D::ZERO)) {
		size = cachedPresentationSize;
		cachedPresentationSize = Vector2D::ZERO;
	}
}
