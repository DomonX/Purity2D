#pragma once

#include "imageRenderer.hpp"
class HudRenderer: public ImageRenderer {
public:
	HudRenderer(): ImageRenderer() {}
protected:
	Transform calculateNewTransform() {
		Vector2D newPosition = transform->getPosition();
		Vector2D newScale = transform->getScale();
		return Transform(newScale, newPosition, transform->getRotation());
	}
};