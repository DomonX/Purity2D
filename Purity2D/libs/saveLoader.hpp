#pragma once

#include <allegro5/allegro.h>
#include <thread>

#include "meshScene.hpp"
#include "filesystemHandler.hpp"
#include "jsonProperty.hpp"

using namespace std;

typedef string (*PostHandler)(Json, Scene*, GameObject*);

string dataForEntites(Json data, Scene* scene, GameObject* go) {
	string sceneName = "";
	int tile = data["id"];
	ObjectType type = ObjectFactory::get()->type(tile, Layer::ENTITIES);
	if (type == ObjectType::PLAYER) {
		sceneName = scene->getName();
		scene->setPlayer(go);
	}
	return sceneName;
}

class SaveLoader {
private:
	string switchSceneName = "";
public:
	void newGame(string mapName) {
		cout << "New Game starting o n thread " << this_thread::get_id() << endl;
		string path = "maps/" + mapName + "/precompilation.json";
		string content = FileSystemHandler().readFile(path);
		GameState::get()->setGameName(mapName);
		Json j = Json::parse(content);
		for (auto& element : j["scenes"]) {
			createScene(element);
		}
		cout << "Finished New Game starting" << endl;
	}

	void load(string mapName, string saveName) {
		cout << "Loading" << endl;
		string path = "saves/" + mapName + "/" + saveName + ".json";
		string content = FileSystemHandler().readFile(path);
		GameState::get()->setGameName(mapName);
		Json j = Json::parse(content);
		for (auto& element : j["scenes"]) {
			createScene(element);
		}
	}
private:
	void fillLayer(Json data, MeshScene* scene, Layer layer, PostHandler goFun = nullptr) {
		for (auto& element : data) {
			int id = element["id"];
			create(id, layer, element, scene, goFun);
		}
	}

	GameObject* create(int code, Layer layer, Json params, Scene* scene, PostHandler goFun) {
		GameObject* result = ObjectFactory::get()->load(code, layer, {scene, params});
		string ret;
		if (goFun) {
			ret = goFun(params, scene, result);
		}
		if (ret != "") {
			switchSceneName = ret;
		}
		return result;
	}

	void createScene(Json j) {
		MeshScene* scene = new MeshScene(j["name"], 16);
		GameState::get()->addScene(scene);
		fillLayer(j["tiles"], scene, Layer::TILES);
		fillLayer(j["objects"], scene, Layer::OBJECTS);
		fillLayer(j["entities"], scene, Layer::ENTITIES, dataForEntites);
		if (switchSceneName != "") {
			GameState::get()->switchScene(switchSceneName);
		}
		scene->setAlpha(true);
		scene->onStart();
	}
};