#pragma once
#include "imageRenderer.hpp"
#include "camera.hpp"
#include "time.hpp"
#include <allegro5/allegro.h>
class FowRenderer: public ImageRenderer {
	ALLEGRO_BITMAP* bmp;
	Vector2D bmpSize;
	ALLEGRO_BITMAP* screen;
public:
	/*ALLEGRO_BITMAP* getImage(Vector2D vec) {
		return bmp;
	}*/

	FowRenderer(): ImageRenderer() {}

	/*!	@copydoc Renderer::calculateNewTransform()	*/
	Transform calculateNewTransform() {
		Vector2D newPosition = transform->getPosition() * GameState::get()->getViewScale();
		Vector2D newScale = transform->getScale() * GameState::get()->getViewScale();
		return Transform(newScale, newPosition, transform->getRotation());
	}

	/*!	@copydoc Component::onStart()	*/
	void onStart() {
		bmpSize = this->transform->getScale();
		bmp = al_create_bitmap(bmpSize.getX(), bmpSize.getY());
		screen = al_get_target_bitmap();
	}

	/*!	@copydoc Component::onUpdate()	*/
	void onUpdate() {
		al_set_target_bitmap(bmp);
		al_clear_to_color(al_map_rgba(0, 0, 0, 255));
		al_set_blender(ALLEGRO_DEST_MINUS_SRC, ALLEGRO_ONE, ALLEGRO_ONE);
		ImageRenderer::onUpdate();
	}

	/*!	@copydoc Component::onRender()	*/
	void onRender() {
		Asset* asset = getAsset();
		ALLEGRO_BITMAP* assetBitmap = asset->getImage();
		Vector2D assetSize = asset->getImageSize();
		al_draw_scaled_bitmap(assetBitmap, 0, 0, assetSize.getX(), assetSize.getY(), 0, 0, bmpSize.getX(), bmpSize.getY(), 0);
	}

	/*!	@copydoc Component::onUpdateAlpha()	*/
	void onUpdateAlpha() {
		Transform current = calculateNewTransform();
		al_set_target_bitmap(screen);
		al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
		renderImage(bmp, current, bmpSize);
	}

	/*!	@copydoc Component::onDelete()	*/
	void onDelete() {
		al_destroy_bitmap(bmp);
	}

	/*!	@copydoc Renderer::isVisible()	*/
	bool isVisible() {
		return true;
	}
};