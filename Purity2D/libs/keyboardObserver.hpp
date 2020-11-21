#pragma once

class KeyboardObserver {
public:
	virtual void onClick(int keycode) {}
	virtual void onHold(int keycode) {}
	virtual void onRelease(int keycode) {}
};