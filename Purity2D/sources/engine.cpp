
#include <chrono>
#include <ctime>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <thread>
#include <windows.h>
#include <signal.h>
#include "../libs/engine.hpp"
#include "../libs/collider.hpp"
#include "../libs/asset.hpp"
#include "../libs/imageRenderer.hpp"
#include "../libs/time.hpp"

Engine* Engine::instance = 0;

Engine* Engine::getInstance() {
    if (instance == 0) {
        instance = new Engine();
    }
    return instance;
}

Engine::Engine(){
	display = nullptr;
	mouse = nullptr;
	keyboard = nullptr;
	gameState = nullptr;
	time = nullptr;
	eventQueue = nullptr;
}

void Engine::onInit() {
	al_init();
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	display = Display::get();
	gameState = GameState::get();
	time = Time::getTime();
	keyboard = Keyboard::get();
	mouse = Mouse::get();
	gameState->onInit();
}

void Engine::onStart() {
	gameState->onStart();
	SetThreadPriority(GetCurrentThread(), 2);
	while (true) {
		auto start = std::chrono::system_clock::now();
		al_clear_to_color(al_map_rgb(0, 0, 0));		
		gameState->onUpdate();
		keyboard->onUpdate();
		mouse->onUpdate();
		al_flip_display();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;
		time->setDeltaTime(elapsedSeconds.count());
	}
}

void Engine::onStop() {
	display->onStop();
	free(display);
}
