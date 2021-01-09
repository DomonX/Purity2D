#pragma once

#include <map>
#include <string>
#include "scene.hpp"
#include "display.hpp"
using namespace std;
class GameState {
private:
	string gameName;
	static GameState* instance;
	map<string, Scene*> scenes;
	vector<string> serializableScenes;
	Scene* currentScene;
	Camera* currentCamera;
	Display* display;
public:

	void onInit() {
		display = Display::get();
	}

	void switchScene(string name) {
		Scene* temp = scenes[name];
		if (temp == nullptr) {
			return;
		}
		currentScene = temp;
		currentCamera = currentScene->getCamera();
	}

	void addScene(Scene* scene, bool serializable = false) {
		scenes[scene->getName()] = scene;
		scene->onStart();
		if (serializable) {
			serializableScenes.push_back(scene->getName());
		}
	}

	Scene* getScene(string name) {
		return scenes[name];
	}

	string getCurrentSceneName() {
		return currentScene->getName();
	}

	void removeScene(Scene* scene) {
		scene->onDelete();
		scenes.erase(scenes.find(scene->getName()), scenes.end());
		free(scene);
	}

	double getViewScale() {
		Vector2D cameraSize = currentScene->getCamera()->getSize();
		Vector2D displaySize = display->getSize();
		double wScale = displaySize.getX() / cameraSize.getX();
		double hScale = displaySize.getY() / cameraSize.getY();
		return wScale > hScale ? wScale : hScale;
	}

	Vector2D getViewPosition() {
		return currentScene->getCamera()->getPosition() - currentScene->getCamera()->getSize() / 2;
	}

	Camera** getCameraHook() {
		return &this->currentCamera;
	}

	Camera* getCurrentCamera() {
		return this->currentCamera;
	}

	void onDelete() {
		for (pair<string, Scene*> i : scenes) {
			removeScene(i.second);
		}
	}

	void onStart() {
		for (pair<string, Scene*> i : scenes) {
			i.second->onStart();
		}
	}

	void onUpdate() {
		currentScene->onUpdate();
		currentScene->onUpdateAlpha();		
	}

	Json save() {
		Json j = Json::object();
		j["name"] = gameName;
		for (pair<string, Scene*> scene : scenes) {
			j["scenes"].push_back(scene.second->serialize());
		}
		return j;
	}

	void setGameName(string name) {
		gameName = name;
	}

	static GameState* get();

private:
	GameState() {
		scenes = map<string, Scene*>();
	}
};