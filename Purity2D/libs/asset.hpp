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
		ALLEGRO_BITMAP * bmp = AssetManager::getAssetManager()->occupy(id, path);
		AssetSized* asset = new AssetSized();
		asset->bmp = bmp;
		asset->height = al_get_bitmap_height(bmp);
		asset->width = al_get_bitmap_width(bmp);
		asset->imageId = path;
		assetSizes.push_back(asset);
	}

	/*!
		\brief Lifecycle hook for deleting asset component
	*/
	void onDelete() {
		AssetManager::getAssetManager()->unsign(id);
		for (AssetSized* asset : assetSizes) {
			free(asset);
		}
	}

	/*! 
		\brief Method for getting displayable bitmap
		\param size Desired size of image
		\returns An Bitmap that is closest possible to desired size
	*/
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

	Component* clone() {
		return this;
	}
};