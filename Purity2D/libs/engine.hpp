#pragma once
#include "display.hpp"
#include "gameState.hpp"
#include "transform.hpp"
#include "component.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "gameObject.hpp"
#include "renderer.hpp"
#include "imageRenderer.hpp"
#include "collider.hpp"
#include "keyboard.hpp"

class Engine {
private:
    static Engine* instance;
	Display* display;
	GameState* gameState;
	Time* time;
	Keyboard* keyboard;
    Engine();
public:
	/*!
		\brief Getter method for Engine singleton
		\returns Global Engine element
	*/
    static Engine* getInstance();
	/*!	\brief Lifecycle hook called when engine starts */
	void onStart();
	/*!	\brief Lifecycle hook called when engine is initialized */
	void onInit();
	/*!	\brief Lifecycle hook called when engine stops */
	void onStop();
};