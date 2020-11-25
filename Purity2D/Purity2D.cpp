#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "libs/engine.hpp"
#include "libs/keyboard.hpp"
#include "libs/controller.hpp"
#include "libs/hudRenderer.hpp"
#include "libs/exampleScript.hpp"
#include "libs/fowRenderer.hpp"
#include "libs/lightRenderer.hpp"

#define TILE_SIZE 16

using namespace std;

GameObject* createTile(int x, int y, Asset* wallType) {
	GameObject* wall = new GameObject();
	wall->addComponent(new ImageRenderer());
	wall->addComponent(wallType);
	wall->addComponent(new Transform(Vector2D(TILE_SIZE, TILE_SIZE), Vector2D(y * TILE_SIZE, x * TILE_SIZE), Rotation(0)));
	return wall;
}

GameObject* createHud(int x, int y, int w, int h, Asset* hudType) {
	GameObject* wall = new GameObject();
	wall->addComponent(new HudRenderer());
	wall->addComponent(hudType);
	wall->addComponent(new Transform(Vector2D(w, h), Vector2D(x, y), Rotation(0)));
	return wall;
}

int main() {
	Engine* en = Engine::getInstance();
	GameState* gs = GameState::get();

	en->onInit();

	// Creating Scenes
	Scene* mainScene = new Scene("Main");
	Camera* cam = mainScene->getCamera();
	gs->addScene(mainScene);

	Scene* testScene = new Scene("Main2");
	Camera* cam2 = testScene->getCamera();
	gs->addScene(testScene);

	Asset* fov = new Asset("fov");
	fov->load("fow3.png");

	Asset* fd = new Asset("floor/fd");
	fd->load("floor/f-d.jpg");
	Asset* fu = new Asset("floor/fu");
	fu->load("floor/f-u.jpg");
	Asset* fr = new Asset("floor/fr");
	fr->load("floor/f-r.jpg");
	Asset* fl = new Asset("floor/fl");
	fl->load("floor/f-l.jpg");
	Asset* fru = new Asset("floor/fru");
	fru->load("floor/f-ru.jpg");
	Asset* frd = new Asset("floor/frd");
	frd->load("floor/f-rd.jpg");
	Asset* fld = new Asset("floor/fld");
	fld->load("floor/f-ld.jpg");
	Asset* flu = new Asset("floor/flu");
	flu->load("floor/f-lu.jpg");
	Asset* fc = new Asset("floor/fc");
	fc->load("floor/f-c.jpg");

	Asset* wd = new Asset("wall/wd");
	wd->load("wall/w-d.jpg");
	Asset* wu = new Asset("wall/wu");
	wu->load("wall/w-u.jpg");
	Asset* wr = new Asset("wall/wr");
	wr->load("wall/w-r.jpg");
	Asset* wl = new Asset("wall/wl");
	wl->load("wall/w-l.jpg");
	Asset* wru = new Asset("wall/wru");
	wru->load("wall/w-ru.jpg");
	Asset* wrd = new Asset("wall/wrd");
	wrd->load("wall/w-rd.jpg");
	Asset* wld = new Asset("wall/wld");
	wld->load("wall/w-ld.jpg");
	Asset* wlu = new Asset("wall/wlu");
	wlu->load("wall/w-lu.jpg");

	Asset* bar = new Asset("bar");
	bar->load("bar.png");

	Asset* light = new Asset("light");
	light->load("light.png");

	// Creating Game Objects

	for (int j = 0; j < 50; j++) {
		int tunnel = j*6;
		int line = 0;
		mainScene->addGameObject(createTile(line, tunnel + 0, wlu));
		mainScene->addGameObject(createTile(line, tunnel + 1, wu));
		mainScene->addGameObject(createTile(line, tunnel + 2, wu));
		mainScene->addGameObject(createTile(line, tunnel + 3, wu));
		mainScene->addGameObject(createTile(line, tunnel + 4, wru));
		line++;

		mainScene->addGameObject(createTile(line, tunnel + 0, wl));
		mainScene->addGameObject(createTile(line, tunnel + 1, flu));
		mainScene->addGameObject(createTile(line, tunnel + 2, fu));
		mainScene->addGameObject(createTile(line, tunnel + 3, fru));
		mainScene->addGameObject(createTile(line, tunnel + 4, wr));
		line++;

		for (int i = 0; i < 50; i++) {
			mainScene->addGameObject(createTile(line, tunnel + 0, wl));
			mainScene->addGameObject(createTile(line, tunnel + 1, fl));
			mainScene->addGameObject(createTile(line, tunnel + 2, fc));
			mainScene->addGameObject(createTile(line, tunnel + 3, fr));
			mainScene->addGameObject(createTile(line, tunnel + 4, wr));
			line++;
		}

		mainScene->addGameObject(createTile(line, tunnel + 0, wl));
		mainScene->addGameObject(createTile(line, tunnel + 1, fld));
		mainScene->addGameObject(createTile(line, tunnel + 2, fd));
		mainScene->addGameObject(createTile(line, tunnel + 3, frd));
		mainScene->addGameObject(createTile(line, tunnel + 4, wr));
		line++;

		mainScene->addGameObject(createTile(line, tunnel + 0, wld));
		mainScene->addGameObject(createTile(line, tunnel + 1, wd));
		mainScene->addGameObject(createTile(line, tunnel + 2, wd));
		mainScene->addGameObject(createTile(line, tunnel + 3, wd));
		mainScene->addGameObject(createTile(line, tunnel + 4, wrd));
		line++;
	}

	GameObject* lightg = new GameObject();
	lightg->addComponent(light);
	lightg->addComponent(new Transform(Vector2D(200, 200), Vector2D(0, 0), Rotation(0)));
	lightg->addComponent(new LightRenderer());
	mainScene->addGameObject(lightg);

	GameObject* lightg2 = new GameObject();
	lightg2->addComponent(light);
	lightg2->addComponent(new Transform(Vector2D(200, 200), Vector2D(200, 200), Rotation(0)));
	lightg2->addComponent(new LightRenderer());
	mainScene->addGameObject(lightg2);


	/*mainScene->addGameObject(createHud(0, 0, cam->getSize().getX(), cam->getSize().getY(), fov));*/
	mainScene->addGameObject(createHud(90, 10, 180, 20, bar));
	
	GameObject* script = new GameObject();
	script->addComponent(new ExampleScript());
	mainScene->addGameObject(script);

	GameObject* player = new GameObject();
	player->addComponent(new Transform(Vector2D(15, 15), Vector2D(20, 20), Rotation(0), 1));
	player->addComponent(new Renderer());
	player->addComponent(new Collider());
	player->addComponent(new Controller());
	mainScene->addGameObject(player);
	player->addGameObject(cam);

	GameObject* fogOfWar = new GameObject();
	fogOfWar->addComponent(new FowRenderer());
	fogOfWar->addComponent(fov);
	mainScene->createFog(fogOfWar);


	GameObject* test3 = new GameObject();
	test3->addComponent(new Transform(Vector2D(300, 300), Vector2D(0, 0), Rotation(0)));
	test3->addComponent(new Renderer());
	testScene->addGameObject(test3);

	GameObject* player2 = new GameObject();
	player2->addComponent(new Transform(Vector2D(15, 15), Vector2D(20, 20), Rotation(0), 1));
	player2->addComponent(new Renderer());
	player2->addComponent(new Collider());
	player2->addComponent(new Controller());
	testScene->addGameObject(player2);
	player2->addGameObject(cam2);

	// Setting Up scene
	gs->switchScene("Main");

	Display::get()->setResolution(1920 / 2, 1080 / 2);

	en->onStart();
	en->onStop();
    return 0;
}
