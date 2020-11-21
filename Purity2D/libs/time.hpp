#pragma once
class Time {
private:
	double deltaTime;
	static Time* instance;
	Time();
public:
	static double getDeltaTime();
	void setDeltaTime(double deltaTime);
	static Time* getTime();
};