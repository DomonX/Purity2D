#pragma once
class Time {
private:
	double deltaTime;
	static Time* instance;
	Time();
public:
	/*!	\brief Returns Change in Time between this frame and last frame */
	static double getDeltaTime();
	/*!	\brief Registers change in Time \warning Shouldn't be used by user */
	void setDeltaTime(double deltaTime);
	/*!	\brief Returns global Time object \warning Shouldn't be used by user, instead use Time::getDeltaTime() as static member */
	static Time* getTime();
};