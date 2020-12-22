#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "libs/engine.hpp"
#include "libs/keyboard.hpp"
#include "libs/controller.hpp"
#include "libs/hudRenderer.hpp"
#include "libs/exampleScript.hpp"
#include "libs/fogRenderer.hpp"
#include "libs/lightRenderer.hpp"
#include "libs/scene.hpp"
#include "libs/planeScene.h"
#include "libs/meshScene.hpp"
#include "libs/mesh.hpp"
#include "libs/cameraVisiblity.hpp"
#include "libs/shaderAsset.h"

#define TILE_SIZE 16

Asset* fd;
Asset* fu;
Asset* fr;
Asset* fl;
Asset* fru;
Asset* frd;
Asset* fld;
Asset* flu;
Asset* fc;

Asset* wd;
Asset* wu;
Asset* wr;
Asset* wl;
Asset* wru;
Asset* wrd;
Asset* wld;
Asset* wlu;

using namespace std;

GameObject* createTile(Asset* wallType) {
	GameObject* tile = new GameObject();
	tile->addComponent(new ImageRenderer());
	tile->addComponent(new Visibility());
	tile->addComponent(wallType);
	tile->addComponent(new Transform(Vector2D(1, 1), Vector2D::ZERO, Rotation()));
	return tile;
}

GameObject* createHud(int x, int y, int w, int h, Asset* hudType) {
	GameObject* wall = new GameObject();
	wall->addComponent(new HudRenderer());
	wall->addComponent(new Visibility());
	wall->addComponent(hudType);
	wall->addComponent(new Transform(Vector2D(w, h), Vector2D(x, y), Rotation(0)));
	return wall;
}

void createTunnel(int x, MeshScene* scene, int len) {
	int j = 0;
	scene->addGameObject(createTile(wlu), Vector2D(x + 0, j), 0);
	scene->addGameObject(createTile(wu), Vector2D(x + 1, j), 0);
	scene->addGameObject(createTile(wu), Vector2D(x + 2, j), 0);
	scene->addGameObject(createTile(wu), Vector2D(x + 3, j), 0);
	scene->addGameObject(createTile(wru), Vector2D(x + 4, j), 0);

	j++;

	scene->addGameObject(createTile(wl), Vector2D(x + 0, j), 0);
	scene->addGameObject(createTile(flu), Vector2D(x + 1, j), 0);
	scene->addGameObject(createTile(fu), Vector2D(x + 2, j), 0);
	scene->addGameObject(createTile(fru), Vector2D(x + 3, j), 0);
	scene->addGameObject(createTile(wr), Vector2D(x + 4, j), 0);

	j++;

	for (j; j < len; j++) {
		scene->addGameObject(createTile(wl), Vector2D(x + 0, j), 0);
		scene->addGameObject(createTile(fl), Vector2D(x + 1, j), 0);
		scene->addGameObject(createTile(fc), Vector2D(x + 2, j), 0);
		scene->addGameObject(createTile(fr), Vector2D(x + 3, j), 0);
		scene->addGameObject(createTile(wr), Vector2D(x + 4, j), 0);
	}

	scene->addGameObject(createTile(wl), Vector2D(x + 0, j), 0);
	scene->addGameObject(createTile(fld), Vector2D(x + 1, j), 0);
	scene->addGameObject(createTile(fd), Vector2D(x + 2, j), 0);
	scene->addGameObject(createTile(frd), Vector2D(x + 3, j), 0);
	scene->addGameObject(createTile(wr), Vector2D(x + 4, j), 0);

	j++;

	scene->addGameObject(createTile(wld), Vector2D(x + 0, j), 0);
	scene->addGameObject(createTile(wd), Vector2D(x + 1, j), 0);
	scene->addGameObject(createTile(wd), Vector2D(x + 2, j), 0);
	scene->addGameObject(createTile(wd), Vector2D(x + 3, j), 0);
	scene->addGameObject(createTile(wrd), Vector2D(x + 4, j), 0);
}

int main() {
	Engine* en = Engine::getInstance();
	GameState* gs = GameState::get();

	en->onInit();

	// Creating Scenes
	MeshScene* mainScene = new MeshScene("Main", 16);
	Camera* cam = mainScene->getCamera();
	gs->addScene(mainScene);

	PlaneScene* testScene = new PlaneScene("Main2");
	Camera* cam2 = testScene->getCamera();
	gs->addScene(testScene);

	Asset* fov = new Asset("fow3.png");

	Asset* bar = new Asset("bar.png");

	Asset* light = new Asset("light.png");

	PartitionConfig wallShader = PartitionConfig("SimpleShaders.png", 2, 2);
	vector<ALLEGRO_BITMAP*>	shaders = AssetManager::get()->partition(wallShader);

	ALLEGRO_BITMAP* floor = AssetManager::get()->occupy("floor.jpg");
	ALLEGRO_BITMAP* wall = AssetManager::get()->occupy("wall.png");

	fd = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::DOWN) });
	fu = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::UP) });
	fr = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::RIGHT) });
	fl = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::LEFT) });
	fru = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::RIGHT), ShaderPart(1, SideShaderRotation::UP) });
	frd = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::RIGHT), ShaderPart(1, SideShaderRotation::DOWN) });
	fld = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::LEFT), ShaderPart(1, SideShaderRotation::DOWN) });
	flu = new ShaderAsset("floor.jpg", wallShader, { ShaderPart(1, SideShaderRotation::LEFT), ShaderPart(1, SideShaderRotation::UP) });
	fc = new Asset("floor.jpg");

	wd = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::UP ) });
	wu = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::DOWN ), ShaderPart(1, SideShaderRotation::UP) });
	wr = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::RIGHT), ShaderPart(1, SideShaderRotation::LEFT) });
	wl = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::LEFT), ShaderPart(1, SideShaderRotation::RIGHT) });
	wru = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::UP), ShaderPart(0, SideShaderRotation::RIGHT), ShaderPart(3, CornerShaderRotation::LEFTDOWN) });
	wrd = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::DOWN), ShaderPart(0, SideShaderRotation::RIGHT), ShaderPart(3, CornerShaderRotation::LEFTUP) });
	wld = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::DOWN), ShaderPart(0, SideShaderRotation::LEFT), ShaderPart(3, CornerShaderRotation::RIGHTUP) });
	wlu = new ShaderAsset("wall.png", wallShader, { ShaderPart(0, SideShaderRotation::UP), ShaderPart(0, SideShaderRotation::LEFT), ShaderPart(3, CornerShaderRotation::RIGHTDOWN) });

	// Creating Game Objects

	int i = 0;

	for (i = 0; i < 100; i++) {
		createTunnel(i*6, mainScene, 100);
	}

	/*for (i = -100; i < 100; i++) {
		for (j = -100; j < 100; j++) {
			GameObject* tile = new GameObject();
			tile->addComponent(new ImageRenderer());
			tile->addComponent(fc);
			tile->addComponent(new Transform(Vector2D(1,1), Vector2D::ZERO, Rotation()));
			mainScene->addGameObject(tile, Vector2D(i, j), 0);
		}
	}*/

	GameObject* lightg = new GameObject();
	lightg->addComponent(light);
	lightg->addComponent(new Transform(Vector2D(50, 50), Vector2D(0, 0), Rotation(0)));
	lightg->addComponent(new CameraVisibility());
	lightg->addComponent(new LightRenderer());
	mainScene->addLight(lightg);

	GameObject* lightg2 = new GameObject();
	lightg2->addComponent(light);
	lightg2->addComponent(new Transform(Vector2D(50, 50), Vector2D(200, 200), Rotation(0)));
	lightg2->addComponent(new CameraVisibility());
	lightg2->addComponent(new LightRenderer());
	mainScene->addLight(lightg2);

	//mainScene->addGameObject(createHud(90, 10, 180, 20, bar));
	
	/*GameObject* script = new GameObject();
	script->addComponent(new ExampleScript());
	mainScene->addGameObject(script);*/

	GameObject* player = new GameObject();
	player->addComponent(new Transform(Vector2D(1, 1), Vector2D::ZERO, Rotation(0), 1));
	player->addComponent(new Renderer());
	player->addComponent(new CameraVisibility());
	player->addComponent(new Collider());
	player->addComponent(new Controller());
	mainScene->addGameObject(player, Vector2D::ZERO, 1);
	player->addGameObject(cam);

	mainScene->addScript(new ExampleScript());

	// Setting Up scene
	gs->switchScene("Main");

	Display::get()->setResolution(1920 / 1.2, 1080 / 1.2);

	en->onStart();
	en->onStop();
    return 0;
}
