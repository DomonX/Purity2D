#pragma once

#include <allegro5/allegro.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "mouseObserver.hpp"
#include "vector2d.hpp"
#include "gameState.hpp"

using namespace std;

class Mouse {
private:
	static Mouse* instance;
	vector<MouseObserver*> observers;
	Mouse();
public:

	void onUpdate() {
		ALLEGRO_MOUSE_STATE state;

		al_get_mouse_state(&state);

		axes(Vector2D(state.x, state.y));
		
		if (al_mouse_button_down(&state, 1)) {
			click(ClickType::LEFT);
		}

		if (al_mouse_button_down(&state, 1)) {
			click(ClickType::RIGHT);
		}
	}

	void axes(Vector2D pos) {
		string currentScene = GameState::get()->getCurrentSceneName();
		for (MouseObserver* obs : observers) {
			SceneElement* sc = dynamic_cast<SceneElement*>(obs);
			if (!sc) {
				continue;
			}
			if (sc->getScene() == currentScene) {
				obs->mouseMove(pos);
			}
		}
	}

	void click(ClickType click) {
		string currentScene = GameState::get()->getCurrentSceneName();
		for (MouseObserver* obs : observers) {
			SceneElement* sc = dynamic_cast<SceneElement*>(obs);
			if (!sc) {
				continue;
			}
			if (sc->getScene() == currentScene) {
				obs->mouseClick(click);
			}
		}
	}

	void unclick() {
		string currentScene = GameState::get()->getCurrentSceneName();
		for (MouseObserver* obs : observers) {
			SceneElement* sc = dynamic_cast<SceneElement*>(obs);
			if (!sc) {
				continue;
			}
			if (sc->getScene() == currentScene) {
				obs->mouseRelease();
			}
		}
	}

	void subscribe(MouseObserver* obs) {
		observers.push_back(obs);
	}

	void unsubscribe(MouseObserver* obs) {
		remove_if(observers.begin(), observers.end(), [obs](MouseObserver* o) { return o == obs; });
	}

	static Mouse* get();
};