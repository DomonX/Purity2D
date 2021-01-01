#pragma once
#include "imageRenderer.hpp"
#include "gameState.hpp"
class LightRenderer : public ImageRenderer {
public:
	LightRenderer(): ImageRenderer() {}
	void onUpdate() {
		ImageRenderer::onUpdate();
	}
	void onUpdateAlpha() {
		ALLEGRO_BITMAP* bmp = image->getImage();
		Transform current = calculateLight();
		renderImage(bmp, current, image->getImageSize());
	}
	Transform calculateLight() {
		Vector2D newPosition = (transform->getPosition() - GameState::get()->getViewPosition());
		Vector2D newScale = transform->getScale() * 7;
		return Transform(newScale, newPosition, transform->getRotation());
	}
};