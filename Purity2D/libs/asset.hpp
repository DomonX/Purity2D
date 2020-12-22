#pragma once
#include "assetManager.hpp"
#include "component.hpp"
#include "vector2d.hpp"
#include <vector>
#include <math.h>
#include <allegro5/allegro.h>
using namespace std;

class Asset : public Component {
protected:
	string path;
	ALLEGRO_BITMAP* asset;
	Vector2D assetSize;
public:

	Asset(string path) {
		this->path = path;
		load();
	}

	void onDelete() {
		AssetManager::get()->release(path);
	}

	ALLEGRO_BITMAP* getImage() {
		return asset;
	}

	Vector2D getImageSize() {
		return assetSize;
	}

	Component* clone() {
		return this;
	}

protected:

	Asset() {
		this->path = "";
	}

	void load() {
		asset = AssetManager::get()->occupy(path);
		assetSize = Vector2D(al_get_bitmap_width(asset), al_get_bitmap_height(asset));
	}
};