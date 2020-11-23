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
	/*!
		@copydoc Component::onGetOtherComponent(Component*)
		\warning There should be Transform component connected to the same GameObject
		\see Transform
	*/
	void onGetOtherComponent(Component* component) {
		this->storeIfIsInstance(&transform, component);
	}

	/*!
		@copydoc Component::onStart()
		\warning All keys used by Controller should be subscribed on Keyboard with
		Usage Keyboard::get()->subscribe(ALLEGRO_KEY_W, this);
		\see Component Keyboard
	*/
	void onStart() {
		Keyboard::get()->subscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->subscribe(ALLEGRO_KEY_S, this);
	}

	/*!
		@copydoc Component::onUpdate()
		\see Component
	*/
	void onUpdate() {
		Component::onUpdate();
	}

	/*!
		@copydoc Component::onDelete()
		\see Component
	*/
	void onDelete() {
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_W, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_A, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_D, this);
		Keyboard::get()->unsubscribe(ALLEGRO_KEY_S, this);
	}

	/*!
		@copydoc KeyboardObserver::onClick()
		\see KeyboardObserver
	*/
	void virtual onClick(int keycode) {
		Transform newTransform = Transform(this->transform);
		if (keycode == ALLEGRO_KEY_W) {
			newTransform = newTransform + Vector2D::UP * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_A) {
			newTransform = newTransform + Vector2D::LEFT * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_D) {
			newTransform = newTransform + Vector2D::RIGHT * Time::getDeltaTime() * 200;
		}
		if (keycode == ALLEGRO_KEY_S) {
			newTransform = newTransform + Vector2D::DOWN * Time::getDeltaTime() * 200;
		}
		(*this->transform) = newTransform;
	}

	virtual Component* clone() {
		return new Controller();
	}
};