#pragma once

class KeyboardObserver {
public:
	/*!	\brief Lifecycle hook called once when button is clicked	*/
	virtual void onClick(int keycode) {}
	/*!	\brief Lifecycle hook called multiple times when button is clicked	*/
	virtual void onHold(int keycode) {}
	/*!	\brief Lifecycle hook called once when button is released	*/
	virtual void onRelease(int keycode) {}
};