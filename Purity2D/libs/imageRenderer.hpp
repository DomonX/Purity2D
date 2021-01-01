#pragma once
#include "renderer.hpp"
#include "asset.hpp"
#include <allegro5/allegro.h>

class ImageRenderer : public Renderer {
protected:
	Asset* image = nullptr;
	ALLEGRO_COLOR tint;
	bool isTinted;

	void renderImage(ALLEGRO_BITMAP* image, Transform current, Vector2D size) {
		Vector2D currentScale = current.getScale();
		Vector2D currentPosition = current.getPosition();
		float xScale = currentScale.getX() / size.getX();
		float yScale = currentScale.getY() / size.getY();
		if (isTinted) {
			al_draw_tinted_scaled_rotated_bitmap(
				image,
				tint,
				size.getX() / 2,
				size.getY() / 2,
				currentPosition.getX(),
				currentPosition.getY(),
				xScale,
				yScale,
				current.getRotation().getAngle(),
				0
			);
		} else {
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
	}
public:
	ImageRenderer() : Renderer() {
		isTinted = false;
		tint = al_map_rgb(0, 0, 0);
	}
	ImageRenderer(ALLEGRO_COLOR color): Renderer() {
		isTinted = true;
		tint = color;
	}

	void onGetOtherComponent(Component* component) {
		Renderer::onGetOtherComponent(component);
		storeIfIsInstance(&image, component);
	}
	void onRender() {
		ALLEGRO_BITMAP* bmp = image->getImage();
		Transform current = calculateNewTransform();
		renderImage(bmp, current, image->getImageSize());
	}

	bool renderConditions() {
		return Renderer::renderConditions() && image != nullptr;
	}

	virtual Component* clone() {
		return new ImageRenderer();
	}
};