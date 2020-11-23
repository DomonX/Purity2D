#pragma once
#include "renderer.hpp"
#include "asset.hpp"
#include <allegro5/allegro.h>

class ImageRenderer : public Renderer {
private:
	Asset* image = nullptr;
	Asset* externalAssetHook = nullptr;
	Asset* getImage() {
		if (externalAssetHook != nullptr) {
			return externalAssetHook;
		}
		return image;
	}
public:
	/*!
		@copydoc Renderer::onGetOtherComponent(Component*)
		\warning There should be Asset and Transform component connected to the same GameObject
		\see Asset Transform
	*/
	void onGetOtherComponent(Component* component) {
		Renderer::onGetOtherComponent(component);
		storeIfIsInstance(&image, component);
	}
	/*!	@copydoc Rendererable::onRender() */
	void onRender() {
		//Renderer::onRender();
		Transform current = calculateNewTransform();
		ALLEGRO_BITMAP* bmp = getImage()->getImage(current.getScale());
		Vector2D currentScale = current.getScale();
		Vector2D currentPosition = current.getPosition();
		int bitmapWidth = al_get_bitmap_width(bmp);
		int bitmapHeight = al_get_bitmap_height(bmp);
		float xScale = currentScale.getX() / bitmapWidth;
		float yScale = currentScale.getY() / bitmapHeight;
		al_draw_scaled_rotated_bitmap(
			bmp,
			bitmapWidth/2,
			bitmapHeight/2,
			currentPosition.getX(),
			currentPosition.getY(),
			xScale,
			yScale,
			current.getRotation().getAngle(),
			0
		);
	}
	/*! \brief Returns external hook for Asset which can be modified from other component to perform animations */
	Asset** hookAsset() {
		return &externalAssetHook;
	}

	/*! @copydoc Renderer::renderConditions() */
	bool renderConditions() {
		return Renderer::renderConditions() && getImage() != nullptr;
	}

	virtual Component* clone() {
		return new ImageRenderer();
	}
};