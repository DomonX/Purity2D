
#include <chrono>
#include <ctime>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <thread>
#include "../libs/engine.hpp"

Engine* Engine::instance = 0;

Engine* Engine::getInstance() {
    if (instance == 0) {
        instance = new Engine();
    }
    return instance;
}

Engine::Engine(){
	display = nullptr;
}

void Engine::init() {
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_image_addon();
	display = new Display();
}

void Engine::start() {
	ALLEGRO_KEYBOARD_STATE keyboard;
	while (true) {
		auto start = std::chrono::system_clock::now();
		al_clear_to_color(al_map_rgb(255, 255, 255));		
		al_flip_display();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Engine::stop() {
	display->stop();
	free(display);
}
