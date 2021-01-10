#pragma once

#include "asset.hpp"

class Sprite : public Asset {
private:
	int w;
	int h;
	vector<ALLEGRO_BITMAP*> bitmaps;
	PartitionConfig conf;
public:
	Sprite(string path, int w, int h) : Asset() {
		this->path = path;
		this->w = w;
		this->h = h;
		load();
	}

	virtual void load() {
		conf = PartitionConfig(path, w, h);
		bitmaps = AssetManager::get()->partition(conf);
		asset = bitmaps.at(0);
		assetSize = Vector2D(al_get_bitmap_width(asset), al_get_bitmap_height(asset));
	}

	void onDelete() {
		AssetManager::get()->unpartition(conf);
	}

	void change(int x, int y) {
		if (x >= w || y >= h) {
			return;
		}
		this->asset = bitmaps.at(y * h + x);
	}

};