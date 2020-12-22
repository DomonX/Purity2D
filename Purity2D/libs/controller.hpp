#pragma once
#include "component.hpp"
#include "keyboardObserver.hpp"
#include "keyboard.hpp"
#include "transform.hpp"
#include "time.hpp"
#include "collider.hpp"
class Controller : public Component, public KeyboardObserver {
private:
	Transform* transform = nullptr;
	Collider* collider = nullptr;
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
		Transform newTransform = Transform(this->transform);
		if (keycode == ALLEGRO_KEY_W) {
			newTransform = newTransform + Vector2D::UP * Time::getDeltaTime() * 75;
		}
		if (keycode == ALLEGRO_KEY_A) {
			newTransform = newTransform + Vector2D::LEFT * Time::getDeltaTime() * 75;
		}
		if (keycode == ALLEGRO_KEY_D) {
			newTransform = newTransform + Vector2D::RIGHT * Time::getDeltaTime() * 75;
		}
		if (keycode == ALLEGRO_KEY_S) {
			newTransform = newTransform + Vector2D::DOWN * Time::getDeltaTime() * 75;
		}
		(*this->transform) = newTransform;
	}

	virtual Component* clone() {
		return new Controller();
	}
};