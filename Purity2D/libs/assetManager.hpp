#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <allegro5/allegro.h>

using namespace std;

struct AssetItem {
	vector<string> peers;
	ALLEGRO_BITMAP* bmp;
};

class AssetManager {
private:
	AssetManager();
	static AssetManager* instance;
	map<string, AssetItem*> assets;
	vector<string> assetsNames;
	const string basePath = "assets/";
public:
	/*!
		\brief Returns singleton of AssetManager
		\returns AssetManager
	*/
	static AssetManager* getAssetManager();

	/*!
		\brief Marks image in path as used by Asset of specified id
		\param assetId Id of asset that wants to use image in path
		\param path Path of image in assets folder
		\returns Bitmap
	*/
	ALLEGRO_BITMAP* occupy(string assetId, string path) {
		AssetItem* i = assets[path];
		if (i == nullptr) {
			i = new AssetItem();
			i->bmp = al_load_bitmap((basePath + path).c_str());
		} 
		if (!i->bmp) {
			throw "Trying to open file " + basePath + path + " but it doesnt exists";
		}
		i->peers.push_back(assetId);
		assets[path] = i;
		return i->bmp;
	}

	/*!
		\brief Marks image in path as no longed used by Asset of specified id
		\param assetId Id of asset that wants to release usage of image in path
		\param path Path of image in assets folder
	*/
	void release(string assetId, string imageId) {
		AssetItem* i = assets[imageId];
		if (i == nullptr) {
			throw "Trying to release asset that doesnt exists in assetManager from leech(" + assetId + ") and from path(" + imageId + ")";
		}
		vector<string>::iterator pos = find(i->peers.begin(), i->peers.end(), assetId);
		if (*pos != assetId) {
			return;
		}
		i->peers.erase(pos);
		if (i->peers.size() == 0) {
			al_destroy_bitmap(i->bmp);
			free(i);
			assets.erase(imageId);
		}
	}

	/*!
		\brief Registers asset in system
		\param assetId Id of asset that wants to be registered in system
	*/
	void sign(string assetId) {
		assetsNames.push_back(assetId);
	}

	/*!
		\brief Unregisters asset in system and releases all usages of images in system
		\param assetId Id of asset that wants to be unregistered in system
	*/
	void unsign(string assetId) {
		assetsNames.erase(find(assetsNames.begin(), assetsNames.end(), assetId));
		for (pair<string, AssetItem*> i : assets) {
			release(assetId, i.first);
		}
	}
};