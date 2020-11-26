#pragma once
#include "component.hpp"
#include "keyboardObserver.hpp"
#include "keyboard.hpp"
#include "gameState.hpp"
#include "display.hpp"
class ExampleScript: public Component, public KeyboardObserver {

	void onStart() {
		Keyboard::get()->subscribe(ALLEGRO_KEY_1, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_2, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_3, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_4, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_5, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_6, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_7, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_8, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_9, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_O, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_P, this);
	}

	void onClick(int keycode) {
		if (keycode == ALLEGRO_KEY_1) {
			(*GameState::get()->getCurrentCamera()).resize(Vector2D(1920 / 4, 1080 / 4));
		}
		if (keycode == ALLEGRO_KEY_2) {
			(*GameState::get()->getCurrentCamera()).resize(Vector2D(1920 / 2, 1080 / 2));
		}
		if (keycode == ALLEGRO_KEY_3) {
			Display::get()->setResolution(1920 / 1.5, 1080 / 1.5);
		}
		if (keycode == ALLEGRO_KEY_4) {
			Display::get()->setResolution(1920 / 2, 1080 / 2);
		}
		if (keycode == ALLEGRO_KEY_5) {
			Display::get()->setResolution(1920 / 2.5, 1080 / 2.5);
		}
		if (keycode == ALLEGRO_KEY_6) {
			GameState::get()->switchScene("Main");
		}
		if (keycode == ALLEGRO_KEY_7) {
			GameState::get()->switchScene("Main2");
		}
		if (keycode == ALLEGRO_KEY_8) {
			Display::get()->fullscreen(true);
		}
		if (keycode == ALLEGRO_KEY_9) {
			Display::get()->fullscreen(false);
		}
		if (keycode == ALLEGRO_KEY_O) {
			Display::get()->presentRendering(true);
		}
		if (keycode == ALLEGRO_KEY_P) {
			Display::get()->presentRendering(false);
		}
	}

	void onEnd() {
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_1, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_2, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_3, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_4, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_5, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_6, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_7, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_8, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_9, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_O, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_P, this);
	}
};