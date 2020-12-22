#include "../libs/time.hpp"

Time* Time::instance = nullptr;
using namespace std;
double Time::getDeltaTime() {
	return Time::getTime()->deltaTime;
}

void Time::setDeltaTime(double time) {
	frames++;
	deltaTime = time;
	frameRate += time;
	if (frameRate > 0.25) {
		frameRate -= 0.25;
		cout << frames / 0.25 << endl;
		frames = 0;
	}
}

Time* Time::getTime() {
	if (instance == nullptr) {
		instance = new Time();
	}
	return instance;
}

Time::Time() {
	deltaTime = 0;
	frameRate = 0;
	frames = 0;
}
