#pragma once
#include "display.hpp"
#include "gameState.hpp"
#include "keyboard.hpp"
#include "time.hpp"
#include "mouse.hpp"

using namespace std;

class Engine {
private:
    static Engine* instance;
	Display* display;
	GameState* gameState;
	Time* time;
	Keyboard* keyboard;
	Mouse* mouse;
	ALLEGRO_EVENT_QUEUE* eventQueue;
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

	void waitForEvent();
};