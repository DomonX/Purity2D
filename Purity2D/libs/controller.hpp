#pragma once
#include "component.hpp"
#include "keyboardObserver.hpp"
#include "keyboard.hpp"
#include "transform.hpp"
#include "time.hpp"
class Controller : public Component, public KeyboardObserver {
private:
	Transform* transform = nullptr;
protected:
	void virtual chooseKeys() {};
public:
	void onGetOtherComponent(Component* component) {
		this->storeIfIsInstance(&transform, component);
	}

	void onStart() {
		Keyboard::get()->subscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_S, this);
	}

	void onUpdate() {
		Component::onUpdate();
	}

	void onDelete() {
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_S, this);
	}

	void virtual onClick(int keycode) {
		if (keycode == ALLEGRO_KEY_W) {
			(*transform) = (*transform) + Vector2D::UP * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_A) {
			(*transform) = (*transform) + Vector2D::LEFT * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_D) {
			(*transform) = (*transform) + Vector2D::RIGHT * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_S) {
			(*transform) = (*transform) + Vector2D::DOWN * Time::getDeltaTime() * 200;
		}
	}
};