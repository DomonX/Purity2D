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
	static AssetManager* getAssetManager();

	ALLEGRO_BITMAP* occupy(string leechId, string imageId) {
		AssetItem* i = assets[imageId];
		if (i == nullptr) {
			i = new AssetItem();
			i->bmp = al_load_bitmap((basePath + imageId).c_str());
		} 
		if (!i->bmp) {
			throw "Trying to open file " + basePath + imageId + " but it doesnt exists";
		}
		i->peers.push_back(leechId);
		assets[imageId] = i;
		return i->bmp;
	}

	void release(string leechId, string imageId) {
		AssetItem* i = assets[imageId];
		if (i == nullptr) {
			throw "Trying to release asset that doesnt exists in assetManager from leech(" + leechId + ") and from path(" + imageId + ")";
		}
		vector<string>::iterator pos = find(i->peers.begin(), i->peers.end(), leechId);
		if (*pos != leechId) {
			return;
		}
		i->peers.erase(pos);
		if (i->peers.size() == 0) {
			al_destroy_bitmap(i->bmp);
			free(i);
			assets.erase(imageId);
		}
	}

	void sign(string leechId) {
		assetsNames.push_back(leechId);
	}

	void unsign(string leechId) {
		assetsNames.erase(find(assetsNames.begin(), assetsNames.end(), leechId));
		for (pair<string, AssetItem*> i : assets) {
			release(leechId, i.first);
		}
	}
};