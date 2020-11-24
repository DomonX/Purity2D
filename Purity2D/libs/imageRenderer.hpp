#pragma once
#include "renderer.hpp"
#include "asset.hpp"
#include <allegro5/allegro.h>

class ImageRenderer : public Renderer {
protected:
	Asset* image = nullptr;
	Asset* externalAssetHook = nullptr;
	virtual Asset* getAsset() {
		if (externalAssetHook != nullptr) {
			return externalAssetHook;
		}
		if (image != nullptr) {
			return image;
		}
		return nullptr;
	}
	void renderImage(ALLEGRO_BITMAP* image, Transform current, Vector2D size) {
		Vector2D currentScale = current.getScale();
		Vector2D currentPosition = current.getPosition();
		float xScale = currentScale.getX() / size.getX();
		float yScale = currentScale.getY() / size.getY();
		al_draw_scaled_rotated_bitmap(
			image,
			size.getX() / 2,
			size.getY() / 2,
			currentPosition.getX(),
			currentPosition.getY(),
			xScale,
			yScale,
			current.getRotation().getAngle(),
			0
		);
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
		Asset* asset = getAsset();
		ALLEGRO_BITMAP* bmp = asset->getImage();
		Transform current = calculateNewTransform();
		renderImage(bmp, current, asset->getImageSize());
	}
	/*! \brief Returns external hook for Asset which can be modified from other component to perform animations */
	Asset** hookAsset() {
		return &externalAssetHook;
	}

	/*! @copydoc Renderer::renderConditions() */
	bool renderConditions() {
		return Renderer::renderConditions() && (image != nullptr || externalAssetHook != nullptr);
	}

	virtual Component* clone() {
		return new ImageRenderer();
	}
};