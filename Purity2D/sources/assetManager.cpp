#include "../libs/assetManager.hpp"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::getAssetManager() {
	if (instance == nullptr) {
		instance = new AssetManager();
	}
	return instance;
}

AssetManager::AssetManager() {

}

