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
    static Engine* getInstance();
	void start();
	void init();
	void stop();
};