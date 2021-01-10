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
	bool lastLeftClicked = false;
	bool lastRightClicked = false;
	Mouse();
public:

	void onUpdate() {
		ALLEGRO_MOUSE_STATE state;

		al_get_mouse_state(&state);

		axes(Vector2D(state.x, state.y));

		bool leftClicked = al_mouse_button_down(&state, 1);
		bool rightClicked = al_mouse_button_down(&state, 2);
		
		if (!lastLeftClicked && leftClicked) {
			click(ClickType::LEFT);
		}

		if (lastLeftClicked && !leftClicked) {
			unclick(ClickType::LEFT);
		}

		if (!lastRightClicked && rightClicked) {
			click(ClickType::RIGHT);
		}

		if (lastRightClicked && !rightClicked) {
			unclick(ClickType::RIGHT);
		}

		lastLeftClicked = leftClicked;
		lastRightClicked = rightClicked;

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
		vector<MouseObserver*> cur = vector<MouseObserver*>(observers);
		for (MouseObserver* obs : cur) {
			SceneElement* sc = dynamic_cast<SceneElement*>(obs);
			if (!sc) {
				continue;
			}
			if (sc->getScene() == currentScene) {
				obs->mouseClick(click);
			}
		}
	}

	void unclick(ClickType click) {
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
		observers.erase(remove_if(observers.begin(), observers.end(), [obs](MouseObserver* o) { return o == obs; }));
	}

	static Mouse* get();
};