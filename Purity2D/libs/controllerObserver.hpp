#pragma once

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class ControllerObserver {
public:
	virtual void onMoveStart(Direction dir) {}

	virtual void onMoveEnd() {}

	virtual void onCollide(GameObject* go) {}
};