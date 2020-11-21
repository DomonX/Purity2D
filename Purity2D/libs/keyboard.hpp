#pragma once
#include <allegro5\keyboard.h>
#include <map>
#include <vector>
#include "keyboardObserver.hpp"
using namespace std;
class Keyboard {
private:
	static Keyboard* instance;
	Keyboard();
	ALLEGRO_KEYBOARD_STATE keyboard;
	map<int, vector<KeyboardObserver*>> observers;
	void processKey(int keycode, vector<KeyboardObserver*> observers);
public:
	static Keyboard* get();
	void onUpdate();
	void subscribe(int keycode, KeyboardObserver* obs);
	void unsubscribe(int keycode, KeyboardObserver* obs);
};