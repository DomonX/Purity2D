#pragma once

#include "vector2d.hpp"
#include "sceneElement.hpp"
#include <allegro5/allegro.h>

enum class ClickType { LEFT, RIGHT };


class MouseObserver {
public:
	virtual void mouseClick(ClickType click) {

	}

	virtual void mouseMove(Vector2D pos) {

	}

	virtual void mouseRelease() {
		
	}
};