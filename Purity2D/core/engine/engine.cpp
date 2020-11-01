
#include <chrono>
#include <ctime>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <thread>
#include "engine.hpp"
#include "../transform/transform.hpp"
#include "../renderer/renderer.hpp"
#include "../gameObject/gameObject.hpp"
#include "../component/component.hpp"

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
	Transform* t3 = new Transform(Vector2D(200, 50), Vector2D(350, 400), Rotation(0));
	GameObject test3 = GameObject();
	test3.addComponent(t3);
	test3.addComponent(new Renderer());

	Transform* t4 = new Transform(Vector2D(400, 400), Vector2D(325, 700), Rotation(0));
	GameObject test4 = GameObject();
	test4.addComponent(t4);
	test4.addComponent(new Renderer());
	Vector2D v1 = Vector2D(100, 100);
	Vector2D v2 = Vector2D(100, 300);
	Vector2D v3 = Vector2D(100, 100);
	Vector2D v4 = Vector2D(100, 200);
	ALLEGRO_KEYBOARD_STATE keyboard;
	while (true) {
		auto start = std::chrono::system_clock::now();
		al_clear_to_color(al_map_rgb(255, 255, 255));
		test3.onUpdate();
		test4.onUpdate();
		cout << t3->collides(*t4) << endl;
		al_flip_display();
		al_get_keyboard_state(&keyboard);
		if (al_key_down(&keyboard, ALLEGRO_KEY_W)) {
			(*t3) = (*t3) + Vector2D::UP;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_S)) {
			(*t3) = (*t3) + Vector2D::DOWN;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_D)) {
			(*t3) = (*t3) + Vector2D::RIGHT;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_A)) {
			(*t3) = (*t3) + Vector2D::LEFT;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_UP)) {
			(*t4) = (*t4) + Vector2D::UP;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_DOWN)) {
			(*t4) = (*t4) + Vector2D::DOWN;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_RIGHT)) {
			(*t4) = (*t4) + Vector2D::RIGHT;
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_LEFT)) {
			(*t4) = (*t4) + Vector2D::LEFT;
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Engine::stop() {
	display->stop();
	free(display);
}
