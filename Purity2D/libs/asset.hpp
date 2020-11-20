#pragma once
#include "assetManager.hpp"
#include "component.hpp"
#include "vector2d.hpp"
#include <vector>
#include <math.h>
using namespace std;

struct AssetSized {
	ALLEGRO_BITMAP* bmp;
	string imageId;
	double width;
	double height;
};

class Asset : public Component {
private:
	string id;
	vector<AssetSized *> assetSizes;
public:
	Asset(string id) {
		this->id = id;
		AssetManager::getAssetManager()->sign(id);
	}

	void load(string imageId) {
		ALLEGRO_BITMAP * bmp = AssetManager::getAssetManager()->occupy(id, imageId);
		AssetSized* asset = new AssetSized();
		asset->bmp = bmp;
		asset->height = al_get_bitmap_height(bmp);
		asset->width = al_get_bitmap_width(bmp);
		asset->imageId = imageId;
		assetSizes.push_back(asset);
	}

	void onDelete() {
		AssetManager::getAssetManager()->unsign(id);
		for (AssetSized* asset : assetSizes) {
			free(asset);
		}
	}

	ALLEGRO_BITMAP* getImage(Vector2D size) {
		AssetSized* bestAsset = nullptr;
		for (AssetSized* asset : assetSizes) {
			if (bestAsset == nullptr) {
				bestAsset = asset;
				continue;
			}
			double bestAssetRatio = bestAsset->width - size.getX() + bestAsset->height - size.getY();
			double currAssetRatio = asset->width - size.getX() + asset->height - size.getY();
			if (bestAssetRatio < 0 && currAssetRatio > 0) {
				bestAsset = asset;
			}
			if (abs(bestAssetRatio) > abs(currAssetRatio)) {
				bestAsset = asset;
			}
		}
		if (bestAsset == nullptr) {
			return nullptr;
		}
		return bestAsset->bmp;
	}
};