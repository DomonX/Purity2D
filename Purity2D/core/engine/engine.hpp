#pragma once
#include "../display/display.hpp"

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