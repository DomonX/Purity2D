#pragma once
#include "display.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "gameObject.hpp"
#include "component.hpp"
class Engine {
private:
    static Engine* instance;
	Display* display;
    Engine();
public:
    static Engine* getInstance();
	void start();
	void init();
	void stop();
};