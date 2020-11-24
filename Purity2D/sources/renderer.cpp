#include "../libs/renderer.hpp"
#include "../libs/gameState.hpp"

Transform Renderer::calculateNewTransform() {
	Vector2D newPosition = (transform->getPosition() - GameState::get()->getViewPosition()) * GameState::get()->getViewScale();
	Vector2D newScale = transform->getScale() * GameState::get()->getViewScale();
	return Transform(newScale, newPosition, transform->getRotation());
}

Renderer::Renderer() {
	cameraHook = GameState::get()->getCameraHook();
}