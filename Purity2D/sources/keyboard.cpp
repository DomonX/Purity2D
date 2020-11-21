#include "..\libs\keyboard.hpp"
#include <algorithm>

Keyboard* Keyboard::instance = nullptr;

void Keyboard::processKey(int keycode, vector<KeyboardObserver*> observers) {
	if (!al_key_down(&keyboard, keycode)) {
		return;
	}
	for (KeyboardObserver* observer : observers) {
		observer->onClick(keycode);
	}
}

Keyboard* Keyboard::get() {
	if (instance == nullptr) {
		instance = new Keyboard();
	}
	return instance;
}

void Keyboard::onUpdate() {
	al_get_keyboard_state(&keyboard);
	for (pair<int, vector<KeyboardObserver*>> i : this->observers ) {
		processKey(i.first, i.second);
	}
}

void Keyboard::subscribe(int keycode, KeyboardObserver* obs) {
	this->observers[keycode].push_back(obs);
}

void Keyboard::unsubscribe(int keycode, KeyboardObserver* obs) {
	vector<KeyboardObserver*> obsv = this->observers[keycode];
	vector<vector<KeyboardObserver*>::iterator> removedElements;
	for (vector<KeyboardObserver*>::iterator i = obsv.begin(); i != obsv.end(); i++) {
		if (*i == obs) {
			removedElements.push_back(i);
		}
	}
	for (vector<KeyboardObserver*>::iterator i : removedElements) {
		obsv.erase(i);
	}
}

Keyboard::Keyboard() {}
