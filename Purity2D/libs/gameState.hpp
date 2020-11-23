#pragma once

#include <map>
#include <string>
#include "scene.hpp"
#include "display.hpp"
#include "renderable.hpp"
using namespace std;
class GameState {
private:
	static GameState* instance;
	map<string, Scene*> scenes;
	map<int, map<int, vector<Renderable*>>> currentRenderables;
	Scene* currentScene;
	Camera* currentCamera;
	Display* display;

public:
	/*!
		\brief Starts GameState
	*/
	void onInit() {
		display = Display::get();
	}

	/*!
		\brief Switches scene
		\param name Name of scene we want to show
	*/
	void switchScene(string name) {
		Scene* temp = scenes[name];
		if (temp == nullptr) {
			return;
		}
		currentScene = temp;
		currentCamera = temp->getCamera();
	}
	/*!
		\brief adds Scene to our game
		\param scene Scene to add to our GameState
		\see Scene
	*/
	void addScene(Scene* scene) {
		scenes[scene->getName()] = scene;
		scene->onStart();
	}

	/*!
		\brief removes Scene from our game
		\param scene Scene to remove from our GameState
		\see Scene
	*/
	void removeScene(Scene* scene) {
		scene->onDelete();
		scenes.erase(scenes.find(scene->getName()), scenes.end());
		free(scene);
	}

	/*!
		\brief Checks difference between display and camera size
		\returns Scale between current camera and display size
		\see Camera
	*/
	double getViewScale() {
		Vector2D cameraSize = currentScene->getCamera()->getSize();
		Vector2D displaySize = display->getSize();
		double wScale = displaySize.getX() / cameraSize.getX();
		double hScale = displaySize.getY() / cameraSize.getY();
		return wScale > hScale ? wScale : hScale;
	}

	/*!
		\brief Returns current position of current Camera
		\returns Vector2D of position
		\see Vector2D Camera
	*/
	Vector2D getViewPosition() {
		return currentScene->getCamera()->getPosition() - currentScene->getCamera()->getSize() / 2;
	}

	/*!
		\brief Hook for current Camera, if Camera changes hook will contain new current Camera
		\returns pointer to current Camera
		\see Camera
	*/
	Camera** getCameraHook() {
		return &this->currentCamera;
	}

	/*! \brief Lifecycle hook that is activated to inform about deleting GameState */
	void onDelete() {
		for (pair<string, Scene*> i : scenes) {
			removeScene(i.second);
		}
	}

	/*! \brief Lifecycle hook that is activated to inform about starting GameState */
	void onStart() {
		for (pair<string, Scene*> i : scenes) {
			i.second->onStart();
		}
	}

	/*! \brief Lifecycle hook that is activated to inform about updating GameState */
	void onUpdate() {
		currentScene->onUpdate();
		render();
	}

	/*! 
		\brief Method used to enqueue Renderable into current frame
		\param layer Layer on which object will be rendered (default is 0) rendered from lowest to highest
		\param pos Position of objects, they are rendered from lowest to highest
		\param rend Renderable element to enqueue
		\see Renderer Renderable
	*/
	void queueRender(int layer, int pos, Renderable* rend) {
		currentRenderables[layer][pos].push_back(rend);
	}
	/*!
		\brief Returns GameState singleton object
	*/
	static GameState* get();

private:
	GameState() {
		scenes = map<string, Scene*>();
	}
	void render() {
		for (pair<int, map<int, vector<Renderable*>>> layer : currentRenderables) {
			renderLayer(layer.second);
		}
		currentRenderables.clear();
	}

	void renderLayer(map<int, vector<Renderable*>> layer) {
		for (pair<int, vector<Renderable*>> rends : layer) {
			renderPosition(rends.second);
		}
	}

	void renderPosition(vector<Renderable*> rends) {
		for (Renderable* rend : rends) {
			rend->onRender();
		}
	}
};