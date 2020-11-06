
#include <chrono>
#include <ctime>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <thread>
#include "../libs/engine.hpp"
#include "../libs/collider.hpp"

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
	display = Display::get();
	gameState = GameState::get();
	gameState->init();
}

void Engine::start() {
	ALLEGRO_KEYBOARD_STATE keyboard;
	Display* dp = Display::get();
	Scene* mainScene = new Scene("Main");
	Camera** cam = gameState->getCameraHook();

	GameObject* test = new GameObject();

	Transform* tr = new Transform(Vector2D(200, 200), Vector2D(300, 300), Rotation(0));
	test->addComponent(tr);
	test->addComponent(new Renderer());

	GameObject* square2 = new GameObject();
	square2->addComponent(new Transform(Vector2D(130, 340), Vector2D(300, 500), Rotation(0)));
	square2->addComponent(new Renderer());
	Collider* col = new Collider();
	square2->addComponent(col);

	gameState->addScene(mainScene);
	gameState->switchScene("Main");

	mainScene->addGameObject(test);
	mainScene->addGameObject(square2);

	gameState->onStart();

	Scene* testScene = new Scene("Main2");
	GameObject* test2 = new GameObject();
	test2->addComponent(new Transform(Vector2D(300, 300), Vector2D(300, 300), Rotation(45)));
	test2->addComponent(new Renderer());
	testScene->addGameObject(test2);
	gameState->addScene(testScene);

	while (true) {
		auto start = std::chrono::system_clock::now();
		al_clear_to_color(al_map_rgb(255, 255, 255));		
		gameState->onUpdate();
		al_flip_display();
		cout << col->collides(*tr) << endl;
		al_get_keyboard_state(&keyboard);
		if (al_key_down(&keyboard, ALLEGRO_KEY_W)) {
			gameState->switchScene("Main2");
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_S)) {
			gameState->switchScene("Main");
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_1)) {
			dp->setResolution(800, 450);
		}
		if (al_key_down(&keyboard, ALLEGRO_KEY_2)) {
			dp->setResolution(1600, 900);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_DOWN)) {
			(*cam)->move(Vector2D::DOWN);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_UP)) {
			(*cam)->move(Vector2D::UP);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_LEFT)) {
			(*cam)->move(Vector2D::LEFT);
		}

		if (al_key_down(&keyboard, ALLEGRO_KEY_RIGHT)) {
			(*cam)->move(Vector2D::RIGHT);
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
