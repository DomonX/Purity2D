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
	/*!	\brief Returns global Keyboard object	*/
	static Keyboard* get();
	/*!	\brief Lifecycle hook called once when frame is rendered	*/
	void onUpdate();
	/*!	\brief Informing keyboard that you wish to be informed about clicks of certain keys	*/
	void subscribe(int keycode, KeyboardObserver* obs);
	/*!	\brief Informing keyboard that you no longer wish to be informed about clicks of certain keys	*/
	void unsubscribe(int keycode, KeyboardObserver* obs);
};