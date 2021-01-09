#include "../libs/mouse.hpp"

Mouse* Mouse::instance = nullptr;

Mouse* Mouse::get() {
	if (instance == 0) {
		instance = new Mouse();
	}
	return instance;
}

Mouse::Mouse() {

}