#pragma once

class ControllerObserver {
public:
	virtual void onMoveStart(Direction dir) {}

	virtual void onMoveEnd() {}

	virtual void onCollide(GameObject* go) {}
};