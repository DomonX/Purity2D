#pragma once

#include <map>
#include <string>
#include "scene.hpp"
#include "display.hpp"
using namespace std;
class GameState {
private:
	static GameState* instance;
	map<string, Scene*> scenes;
	Scene* currentScene;
	Camera* currentCamera;
	Display* display;

	GameState() {
		scenes = map<string, Scene*>();
	}
public:
	void init() {
		display = Display::get();
	}

	void switchScene(string name) {
		Scene* temp = scenes[name];
		if (temp == nullptr) {
			return;
		}
		currentScene = temp;
		currentCamera = temp->getCamera();
	}

	void addScene(Scene* scene) {
		scenes[scene->getName()] = scene;
	}

	void removeScene(Scene* scene) {
		scene->onDelete();
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
		return currentScene->getCamera()->getPosition();
	}

	Camera** getCameraHook() {
		return &this->currentCamera;
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
	}

	static GameState* get();
};