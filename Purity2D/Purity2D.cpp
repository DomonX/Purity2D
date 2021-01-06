#include <iostream>
#include <nlohmann/json.hpp>

#include "libs/engine.hpp"
#include "libs/keyboard.hpp"
#include "libs/controller.hpp"
#include "libs/hudRenderer.hpp"
#include "libs/exampleScript.hpp"
#include "libs/fogRenderer.hpp"
#include "libs/lightRenderer.hpp"
#include "libs/meshScene.hpp"
#include "libs/mesh.hpp"
#include "libs/cameraVisiblity.hpp"
#include "libs/shaderAsset.h"
#include "libs/meshLoader.hpp"
#include "libs/objectFactory.hpp"
#include "libs/drawDecoder.hpp"
#include "libs/wallShader.hpp"
#include "libs/floorShader.hpp"
#include "libs/meshController.hpp"
#include "libs/PlayerMovement.hpp"
#include "libs/meshCollider.hpp"
#include "libs/sprite.hpp"
#include "libs/animator.hpp"
#include "libs/meshAi.hpp"

using namespace std;

GameObject* createWall(CreationData data) {
	GameObject* tile = new GameObject(data.id);
	MeshAdjacent* ad = static_cast<MeshAdjacent*>(data.extra);
	tile->addComponent(new ImageRenderer());
	tile->addComponent(new Visibility());
	Colliders colliders = { { true, true, true, true, false, false, false, false } };
	tile->addComponent(new MeshCollider(colliders));
	tile->addComponent(new ShaderAsset("wall.png", PartitionConfig("SimpleShaders.png", 2, 2), WallShader::shade(ad)));
	tile->addComponent(new Transform(Vector2D(1, 1), Vector2D::ZERO, Rotation()));
	MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
	scene->addGameObject(tile, data.position, 0);
	return tile;
}

GameObject* createTorch(CreationData data) {
	GameObject* torch = new GameObject(data.id);
	torch->addComponent(new ImageRenderer());
	torch->addComponent(new Visibility());
	torch->addComponent(new Asset("torch.png"));
	torch->addComponent(new Transform(Vector2D(0.5, 0.5), Vector2D::ZERO, Rotation()));
	MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
	scene->addGameObject(torch, data.position, 1);
	GameObject* light = new GameObject(0);
	light->addComponent(new Transform(Vector2D(40, 40), scene->calculatePosition(data.position), Rotation()));
	light->addComponent(new LightRenderer());
	light->addComponent(new Asset("light.png"));
	scene->addLight(light);
	return torch;
}


GameObject* createFloor(CreationData data) {
	GameObject* tile = new GameObject(data.id);
	MeshAdjacent* ad = static_cast<MeshAdjacent*>(data.extra);
	tile->addComponent(new ImageRenderer());
	tile->addComponent(new Visibility());
	tile->addComponent(new ShaderAsset("floor.jpg", PartitionConfig("SimpleShaders.png", 2, 2), FloorShader::shade(ad)));
	tile->addComponent(new Transform(Vector2D(1, 1), Vector2D::ZERO, Rotation()));
	MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
	scene->addGameObject(tile, data.position, 0);
	return tile;
}

Animator* getTypicalAnimator() {
	vector<Vector2D> goDown = { Vector2D(1, 0), Vector2D(2, 0), Vector2D(3, 0), Vector2D(0, 0) };
	vector<Vector2D> goLeft = { Vector2D(1, 1), Vector2D(2, 1), Vector2D(3, 1), Vector2D(0, 1) };
	vector<Vector2D> goRight = { Vector2D(1, 2), Vector2D(2, 2), Vector2D(3, 2), Vector2D(0, 2) };
	vector<Vector2D> goUp = { Vector2D(1, 3), Vector2D(2, 3), Vector2D(3, 3), Vector2D(0, 3) };
	map<string, vector<Vector2D>> anims = { {"goDown", goDown }, {"goLeft", goLeft }, {"goRight", goRight }, {"goUp", goUp }, };
	return new Animator(anims);
}

GameObject* createPlayer(CreationData data) {
	GameObject* player = new GameObject(data.id);
	Camera* cam = data.scene->getCamera();
	player->addComponent(new Transform(Vector2D(0.60, 0.75), Vector2D::ZERO, Rotation(0)));
	player->addComponent(new ImageRenderer());
	player->addComponent(new Visibility());
	Colliders colliders = { { true, true, true, true, false, false, false, false } };
	player->addComponent(new MeshCollider(colliders));
	player->addComponent(new Sprite("player.png", 4, 4));
	player->addComponent(new MeshController(3));
	player->addComponent(new PlayerMovement());
	player->addComponent(getTypicalAnimator());
	player->addGameObject(cam);
	MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
	scene->addGameObject(player, data.position, 2);
	return player;
}

GameObject* createEnemy(CreationData data) {
	GameObject* enemy = new GameObject(data.id);
	MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
	enemy->addComponent(new Transform(Vector2D(0.60, 0.75), Vector2D::ZERO, Rotation(0)));
	enemy->addComponent(new ImageRenderer());
	enemy->addComponent(new Visibility());
	Colliders colliders = { { true, true, true, true, false, false, false, false } };
	enemy->addComponent(new MeshCollider(colliders));
	enemy->addComponent(new Sprite("player.png", 4, 4));
	enemy->addComponent(new MeshController(3));
	enemy->addComponent(new MeshAi(scene, 6));
	enemy->addComponent(getTypicalAnimator());
	scene->addGameObject(enemy, data.position, 2);
	return enemy;
}


int main() {
	Engine* en = Engine::getInstance();
	GameState* gs = GameState::get();
	en->onInit();

	using Json = nlohmann::json;

	Json test = { { "name", "xx" } };
	test["id"] = "2";

	Json arr = Json::array();

	arr.push_back(Json::object({ { "propName" , "propValue" } }));
	arr.push_back(Json::object({ { "propName" , "propValue" } }));
	arr.push_back(Json::object({ { "propName" , "propValue" } }));
	arr.push_back(Json::object({ { "propName" , "propValue" } }));

	test["arr"] = arr;

	Json empty;

	Json test2;
	test2["x"] = test;

	cout << test2.dump(4) << endl;

	// Registering Tiles

	DrawDecoder::get()->regist(1, { 0, 162, 232 }, Layer::TILES, createWall, ObjectType::WALL);
	DrawDecoder::get()->regist(2, { 255, 242, 0 }, Layer::TILES, createFloor, ObjectType::FLOOR);

	// Registering Objects

	DrawDecoder::get()->regist(1, { 0, 162, 232 }, Layer::OBJECTS, createTorch, ObjectType::UNKNOWN);

	// Registering Entities

	DrawDecoder::get()->regist(1, { 255, 242, 0 }, Layer::ENTITIES, createPlayer, ObjectType::PLAYER);
	DrawDecoder::get()->regist(2, { 255, 0, 0 }, Layer::ENTITIES, createEnemy, ObjectType::UNKNOWN);

	// Creating Scenes
	MeshScene* mainScene = new MeshScene("Main", 16);
	Camera* cam = mainScene->getCamera();
	mainScene->addScript(new ExampleScript());
	gs->addScene(mainScene);

	PartitionConfig wallShader = PartitionConfig("SimpleShaders.png", 2, 2);
	vector<ALLEGRO_BITMAP*>	shaders = AssetManager::get()->partition(wallShader);

	MeshLoader* loader = new MeshLoader();
	loader->load(mainScene, "tile");

	Asset* fov = new Asset("fow3.png");
	Asset* bar = new Asset("bar.png");
	Asset* light = new Asset("light.png");

	// Setting Up scene
	gs->switchScene("Main");

	Display::get()->setResolution(1920 / 1.2, 1080 / 1.2);

	en->onStart();
	en->onStop();
    return 0;
}
