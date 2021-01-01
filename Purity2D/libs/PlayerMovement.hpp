#pragma once

#include "meshController.hpp"
#include "animator.hpp"
#include "component.hpp"
#include "keyboard.hpp"

class PlayerMovement : public Component, KeyboardObserver {
	MeshController* controller;
	Animator* animator;

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&controller, component);
		storeIfIsInstance(&animator, component);
	}

	void onStart() {
		Keyboard::get()->subscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_S, this);
	}

	void onDelete() {
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_S, this);
	}

	void virtual onClick(int keycode) {
		if (keycode == ALLEGRO_KEY_W) {
			controller->move(Direction::UP);
			animator->animate("goUp", controller->getMovementTime(), false);
			return;
		}
		if (keycode == ALLEGRO_KEY_S) {
			controller->move(Direction::DOWN);
			animator->animate("goDown", controller->getMovementTime(), false);
			return;
		}
		if (keycode == ALLEGRO_KEY_A) {
			controller->move(Direction::LEFT);
			animator->animate("goLeft", controller->getMovementTime(), false);
			return;
		}
		if (keycode == ALLEGRO_KEY_D) {
			controller->move(Direction::RIGHT);
			animator->animate("goRight", controller->getMovementTime(), false);
			return;
		}
	}
};