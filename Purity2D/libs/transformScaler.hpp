#pragma once

#include "transform.hpp"
#include "gameState.hpp"

class TransformScaler {
public:
	Transform scale(Transform t) {
		Vector2D newPosition = (t.getPosition() - GameState::get()->getViewPosition()) * GameState::get()->getViewScale();
		Vector2D newScale = t.getScale() * GameState::get()->getViewScale();
		return Transform(newScale, newPosition, t.getRotation());
	}

	Vector2D scaleVector(Vector2D v) {
		return (v / GameState::get()->getViewScale()) + GameState::get()->getViewPosition();
	}
};