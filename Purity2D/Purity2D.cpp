#include "libs/engine.hpp"
#include "libs/exampleScript.hpp"
#include "libs/drawDecoder.hpp"
#include "libs/mapCompiler.hpp"
#include "libs/saveLoader.hpp"
#include "libs/wall.hpp"
#include "libs/floor.hpp"
#include "libs/torch.hpp"
#include "libs/enemy.hpp"
#include "libs/player.hpp"
#include "libs/planeScene.h"
#include "libs/button.hpp"

using namespace std;

int main() {
	Engine* en = Engine::getInstance();
	GameState* gs = GameState::get();
	en->onInit();

	// Registering Tiles

	DrawDecoder::get()->regist(1, { 0, 162, 232 }, new Wall());
	DrawDecoder::get()->regist(2, { 255, 242, 0 }, new Floor());

	//// Registering Objects

	DrawDecoder::get()->regist(1, { 0, 162, 232 }, new Torch());

	//// Registering Entities

	DrawDecoder::get()->regist(1, { 255, 242, 0 }, new Player());
	DrawDecoder::get()->regist(2, { 255, 0, 0 }, new Enemy());

	PartitionConfig wallShader = PartitionConfig("SimpleShaders.png", 2, 2);
	vector<ALLEGRO_BITMAP*>	shaders = AssetManager::get()->partition(wallShader);

	MapCompiler c = MapCompiler();
	c.compile("exampleMap");

	PlaneScene* scene = new PlaneScene("Menu");
	gs->addScene(scene);

	GameObject* newGameButton = new GameObject(0);
	newGameButton->addComponent(new ImageRenderer());
	newGameButton->addComponent(new Asset("button_new_game.png"));
	newGameButton->addComponent(new Visibility());
	newGameButton->addComponent(new Transform(Vector2D(100, 50), Vector2D(0, -50), Rotation(0)));
	Button* btn = new Button();
	btn->mouse()->onClick = [](Component* button, ClickType click) {
		SaveLoader().newGame("exampleMap");
	};
	newGameButton->addComponent(btn);
	scene->addGameObject(newGameButton);

	GameObject* loadGameButton = new GameObject(0);
	loadGameButton->addComponent(new ImageRenderer());
	loadGameButton->addComponent(new Asset("button_load_game.png"));
	loadGameButton->addComponent(new Visibility());
	loadGameButton->addComponent(new Transform(Vector2D(100, 50), Vector2D(0, 10), Rotation(0)));
	Button* btn2 = new Button();
	btn2->mouse()->onClick = [](Component* button, ClickType click) {
		SaveLoader().load("exampleMap", "save1");
	};
	loadGameButton->addComponent(btn2);
	scene->addGameObject(loadGameButton);

	SaveLoader s = SaveLoader();
	//s.newGame("exampleMap");
	//s.load("exampleMap", "save1");
	gs->switchScene("Menu");

	Display::get()->setResolution(1920 / 1.1, 1080 / 1.1);

	en->onStart();
	en->onStop();
    return 0;
}
