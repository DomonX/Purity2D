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
		Asset* asset = getAsset();
		ALLEGRO_BITMAP* bmp = asset->getImage();
		Transform current = calculateLight();
		renderImage(bmp, current, asset->getImageSize());
	}
	Transform calculateLight() {
		Vector2D newPosition = (transform->getPosition() - GameState::get()->getViewPosition());
		Vector2D newScale = transform->getScale() * 7;
		return Transform(newScale, newPosition, transform->getRotation());
	}
};