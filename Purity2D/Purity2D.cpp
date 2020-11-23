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

	en->onInit();

	// Creating Scenes
	Scene* mainScene = new Scene("Main");
	Camera* cam = mainScene->getCamera();
	gs->addScene(mainScene);

	Scene* testScene = new Scene("Main2");
	Camera* cam2 = testScene->getCamera();
	gs->addScene(testScene);

	Asset* a = new Asset("grass");
	a->load("floor.jpg");

	vector<GameObject*> grassTiles;

	// Creating Game Objects
	GameObject* grassTile = new GameObject();
	grassTile->addComponent(new ImageRenderer());
	grassTile->addComponent(a);
	int tileSize = 16;
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			GameObject* gt = grassTile->clone();
			gt->addComponent(new Transform(Vector2D(tileSize, tileSize), Vector2D(tileSize * j, tileSize * i), Rotation(0)));
			grassTiles.push_back(gt);
			mainScene->addGameObject(gt);
		}
	}

	GameObject* player = new GameObject();
	player->addComponent(new Transform(Vector2D(15, 15), Vector2D(20, 20), Rotation(0), 1));
	player->addComponent(new Renderer());
	player->addComponent(new Collider());
	player->addComponent(new Controller());
	mainScene->addGameObject(player);
	player->addGameObject(cam);

	GameObject* test3 = new GameObject();
	test3->addComponent(new Transform(Vector2D(300, 300), Vector2D(0, 0), Rotation(0)));
	test3->addComponent(new ImageRenderer());
	test3->addComponent(a);
	testScene->addGameObject(test3);

	GameObject* player2 = new GameObject();
	player2->addComponent(new Transform(Vector2D(15, 15), Vector2D(20, 20), Rotation(0), 1));
	player2->addComponent(new Renderer());
	player2->addComponent(new Collider());
	player2->addComponent(new Controller());
	testScene->addGameObject(player);
	player->addGameObject(cam2);

	// Setting Up scene
	gs->switchScene("Main");

	en->onStart();
	en->onStop();
    return 0;
}
