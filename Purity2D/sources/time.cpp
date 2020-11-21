#include "../libs/time.hpp"

Time* Time::instance = nullptr;

double Time::getDeltaTime() {
	return Time::getTime()->deltaTime;
}

void Time::setDeltaTime(double time) {
	deltaTime = time;
}

Time* Time::getTime() {
	if (instance == nullptr) {
		instance = new Time();
	}
	return instance;
}

Time::Time() {
	deltaTime = 0;
}
