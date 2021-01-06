#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <allegro5/allegro.h>
#include <sstream>

#include "rotation.hpp"
#include "shaderPart.hpp"

using namespace std;

enum SideShaderRotation { RIGHT, DOWN, LEFT, UP };
enum CornerShaderRotation { RIGHTUP, RIGHTDOWN, LEFTDOWN, LEFTUP };

struct AssetItem {
	int peers;
	ALLEGRO_BITMAP* bmp;
};

struct PartitionConfig {
	short w;
	short h;
	string path;

	PartitionConfig() {}

	PartitionConfig(string path, short w, short h) {
		this->w = w;
		this->h = h;
		this->path = path;
	}
};

struct PartitionAssetItem {
	int peers;
	vector<ALLEGRO_BITMAP*> partitions;
};

class AssetManager {
private:
	AssetManager();
	static AssetManager* instance;
	map<string, AssetItem*> assets;
	map<string, PartitionAssetItem*> partitionAssets;
	map<string, AssetItem*> shaderAssets;
	const string basePath = "assets/";
public:
	static AssetManager* get();

	ALLEGRO_BITMAP* occupy(string path) {
		AssetItem* i = assets[path];
		if (i == nullptr) {
			i = new AssetItem();
			i->bmp = al_load_bitmap((basePath + path).c_str());
			assets[path] = i;
		}
		if (!i->bmp) {
			throw "Trying to open file " + basePath + path + " but it doesnt exists";
		}
		i->peers++;
		return i->bmp;
	}

	void release(string imageId) {
		AssetItem* i = assets[imageId];
		if (i == nullptr) {
			throw "Trying to release asset that doesnt exists in assetManager path(" + imageId + ")";
		}
		i->peers--;
		if (i->peers == 0) {
			al_destroy_bitmap(i->bmp);
			free(i);
			assets.erase(imageId);
		}
	}

	vector<ALLEGRO_BITMAP*> partition(PartitionConfig conf) {
		string key = getPartitionKey(conf);
		PartitionAssetItem* item = partitionAssets[key];
		if (item) {
			item->peers++;
			return item->partitions;
		}
		item = new PartitionAssetItem();
		item->peers = 1;
		ALLEGRO_BITMAP* bmp = al_load_bitmap((basePath + conf.path).c_str());
		int width = al_get_bitmap_width(bmp);
		int height = al_get_bitmap_height(bmp);

		int partWidth = width / conf.w;
		int partHeight = height / conf.h;

		if (partWidth * conf.w != width || partHeight * conf.h != height) {
			throw "Cannot partition " + key + " beacuse size and partition settings are not compatible with each other";
		}

		for (int i = 0; i < conf.h; i++) {
			for (int j = 0; j < conf.w; j++) {
				ALLEGRO_BITMAP* bmp2 = al_clone_bitmap(al_create_sub_bitmap(bmp, j * partWidth, i * partHeight, partWidth, partHeight));
				item->partitions.push_back(bmp2);
			}
		}

		al_destroy_bitmap(bmp);

		partitionAssets[key] = item;
		return item->partitions;
	}

	void unpartition(PartitionConfig conf) {
		string key = getPartitionKey(conf);
		PartitionAssetItem* i = partitionAssets[key];
		if (i == nullptr) {
			throw "Trying to release asset that doesnt exists in assetManager path(" + key + ")";
		}
		i->peers--;
		if (i->peers == 0) {
			for (ALLEGRO_BITMAP* bmp : i->partitions) {
				al_destroy_bitmap(bmp);
			}
			free(i);
			partitionAssets.erase(key);
		}
	}

	ALLEGRO_BITMAP* shade(string path, PartitionConfig shader, vector<ShaderPart> parts) {
		string key = shaderPartsToKey(path, shader, parts);
		AssetItem* item = shaderAssets[key];
		if (item) {
			item->peers++;
			return item->bmp;
		}
		item = new AssetItem();
		item->peers = 1;

		vector<ALLEGRO_BITMAP*> shaderImages = partition(shader);
		ALLEGRO_BITMAP* element = occupy(path);
		ALLEGRO_BITMAP* shadered = applyShaderParts(al_clone_bitmap(element), shaderImages, parts);
		unpartition(shader);
		release(path);
		item->bmp = shadered;
		shaderAssets[key] = item;
		return shadered;
	}

	//void freeShader(string path, string shaderPath, int shaderW, int shaderH, vector<ShaderPart> parts) {

	//}

private:
	string getPartitionKey(PartitionConfig conf) {
		stringstream ss;
		ss << conf.path << "$" << conf.w << "|" << conf.h;
		return ss.str();
	}

	string shaderPartsToKey(string path, PartitionConfig conf, vector<ShaderPart> parts) {
		stringstream ss;
		ss << path << "$" << getPartitionKey(conf);
		for(ShaderPart part: parts) {
			ss << "," << part.shaderNumber << ":" << part.shaderRotation;
		}
		return ss.str();
	}

	ALLEGRO_BITMAP* applyShaderParts(ALLEGRO_BITMAP* element, vector<ALLEGRO_BITMAP*> shaders, vector<ShaderPart> parts) {
		ALLEGRO_BITMAP* screen = al_get_target_bitmap();
		al_set_target_bitmap(element);
		int width = al_get_bitmap_width(element);
		int height = al_get_bitmap_height(element);
		int shaderWidth = al_get_bitmap_width(shaders.at(0));
		int shaderHeight = al_get_bitmap_height(shaders.at(0));
		float xScale = (float)width / shaderWidth;
		float yScale = (float)height / shaderHeight;
		for (ShaderPart part : parts) {
			Rotation rot = Rotation(part.shaderRotation * 90);
			al_draw_scaled_rotated_bitmap(shaders.at(part.shaderNumber), shaderWidth / 2, shaderHeight / 2, width / 2, height / 2, xScale, yScale, rot.getAngle(), 0);
		}
		al_set_target_bitmap(screen);
		return element;
	}
};