#include "../libs/objectFactory.hpp"

ObjectFactory* ObjectFactory::instance = nullptr;

ObjectFactory* ObjectFactory::get() {
	if (instance == nullptr) {
		instance = new ObjectFactory();
	}
	return instance;
}