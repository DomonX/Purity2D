#pragma once

#include "asset.hpp"

class ShaderAsset : public Asset {
protected:
	PartitionConfig conf;
	vector<ShaderPart> parts;
public:
	ShaderAsset(string path, PartitionConfig conf, vector<ShaderPart> parts) {
		this->path = path;
		this->conf = conf;
		this->parts = parts;
		load();
	}

	JsonProperty serialize() {
		JsonProperty data = JsonProperty("ShaderAsset");
		data.value["shaders"] = Json::array();
		for (ShaderPart part : parts) {
			data.value["shaders"].push_back(Json::object({ { "index" , part.shaderNumber }, { "rotation", part.shaderRotation } }));
		}
		return data;
	}

protected:
	ShaderAsset() {
		asset = nullptr;
	}

	void load() {
		asset = AssetManager::get()->shade(path, conf, parts);
		assetSize = Vector2D(al_get_bitmap_width(asset), al_get_bitmap_height(asset));
	}
};