#include "../lib/engine.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "../lib/transform.hpp"
#include "../lib/renderer.hpp"
#include "../lib/gameObject.hpp"
#include "../lib/component.hpp"
#include <thread>

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
	GameObject test = GameObject();
	Transform * transform = new Transform(Vector2D(100, 100), Vector2D(100, 100), Rotation(0.02));
	Vector2D x = Vector2D(200, 200);
	Vector2D rotVec = Vector2D(0, 0);
	Rotation rot = Rotation(0);
	test.addComponent(transform);
	test.addComponent(new Renderer());
	ALLEGRO_KEYBOARD_STATE keyboard;
	while (true) {
		auto start = std::chrono::system_clock::now();
		// TODO External renderer
		al_clear_to_color(al_map_rgb(255, 255, 255));
		test.onUpdate();
		al_flip_display();
		//al_get_keyboard_state(&keyboard);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Engine::stop() {
	display->stop();
	free(display);
}
