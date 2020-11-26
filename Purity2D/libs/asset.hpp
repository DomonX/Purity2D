#pragma once
#include "assetManager.hpp"
#include "component.hpp"
#include "vector2d.hpp"
#include <vector>
#include <math.h>
#include <allegro5/allegro.h>
using namespace std;

class Asset : public Component {
private:
	string id;
	ALLEGRO_BITMAP* asset;
	Vector2D assetSize;
public:
	/*!
		\brief Constructor of asset
		\param id Unique id of asset
	*/
	Asset(string id) {
		this->id = id;
		AssetManager::getAssetManager()->sign(id);
	}

	/*!
		\brief Method for loading another image for asset
		\param path Path to image in assets folder 
	*/
	void load(string path) {
		asset = AssetManager::getAssetManager()->occupy(id, path);
		assetSize = Vector2D(al_get_bitmap_width(asset), al_get_bitmap_height(asset));
	}

	/*!
		\brief Lifecycle hook for deleting asset component
	*/
	void onDelete() {
		AssetManager::getAssetManager()->unsign(id);
	}

	/*! 
		\brief Method for getting displayable bitmap
		\returns An Bitmap that asset is holding
	*/
	ALLEGRO_BITMAP* getImage() {
		return asset;
	}

	/*!
		\brief Method for getting bitmap size
		\returns Size of asset bitmap
	*/
	Vector2D getImageSize() {
		return assetSize;
	}

	/*!	@copydoc Component::clone()	*/
	Component* clone() {
		return this;
	}
};