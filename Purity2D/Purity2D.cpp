#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "libs/engine.hpp"
#include "libs/keyboard.hpp"
#include "libs/controller.hpp"

using namespace std;

int main() { 
	Engine * en = Engine::getInstance();
	GameState* gs = GameState::get();

	en->init();

	// Creating Scenes
	Scene* mainScene = new Scene("Main");
	Camera* cam = mainScene->getCamera();
	gs->addScene(mainScene);

	Scene* testScene = new Scene("Main2");
	gs->addScene(testScene);

	// Creating Game Objects
	GameObject* test = new GameObject();
	test->addComponent(new Transform(Vector2D(20, 20), Vector2D(0, 0), Rotation(0)));
	test->addComponent(new Renderer());
	test->addComponent(new Collider());
	test->addComponent(new Controller());
	mainScene->addGameObject(test);

	GameObject* test2 = new GameObject();
	test2->addComponent(new Transform(Vector2D(13, 34), Vector2D(20, 20), Rotation(0)));
	test2->addComponent(new Renderer());
	test2->addComponent(new Collider());
	mainScene->addGameObject(test2);

	GameObject* test4 = new GameObject();
	test4->addComponent(new Transform(Vector2D(400, 230), Vector2D(60, 80), Rotation(0)));
	test4->addComponent(new Renderer());
	test4->addComponent(new Collider());
	mainScene->addGameObject(test4);

	//test->addGameObject(test2);
	test->addGameObject(cam);

	Asset* a = new Asset("testAsset");
	a->load("xxx.bmp");
	a->load("xxxx.png");

	GameObject* test3 = new GameObject();
	test3->addComponent(new Transform(Vector2D(300, 300), Vector2D(300, 300), Rotation(45)));
	test3->addComponent(new ImageRenderer());
	test3->addComponent(a);
	testScene->addGameObject(test3);

	// Setting Up scene
	gs->switchScene("Main");
	KeyboardObserver* obs = new KeyboardObserver();

	en->start();
	en->stop();
    return 0;
}
