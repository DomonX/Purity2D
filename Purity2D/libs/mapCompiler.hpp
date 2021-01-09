#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/algorithm/string.hpp>

#include "filesystemHandler.hpp"
#include "jsonProperty.hpp"
#include "asset.hpp"
#include "drawDecoder.hpp"
#include "meshAdjacent.hpp"

typedef boost::numeric::ublas::matrix<int> Tiles;
typedef void* (*DataCreator)(Tiles, Vector2D);

using namespace std;

int tileAt(Tiles tiles, Vector2D pos, Vector2D size) {
	if (pos.getX() < 0 || pos.getY() < 0) {
		return 0;
	}
	if (pos.getX() > size.getX() - 1 || pos.getY() > size.getY() - 1) {
		return 0;
	}
	return tiles(pos.getX(), pos.getY());
}

void* dataForTiles(Tiles tiles, Vector2D position) {
	Vector2D size = Vector2D(tiles.size1(), tiles.size2());
	MeshAdjacent* ad = new MeshAdjacent();
	ad->adjacent[0] = tileAt(tiles, position + Vector2D(-1, -1), size);
	ad->adjacent[1] = tileAt(tiles, position + Vector2D(0, -1), size);
	ad->adjacent[2] = tileAt(tiles, position + Vector2D(1, -1), size);
	ad->adjacent[3] = tileAt(tiles, position + Vector2D(-1, 0), size);
	ad->adjacent[4] = tileAt(tiles, position + Vector2D(1, 0), size);
	ad->adjacent[5] = tileAt(tiles, position + Vector2D(-1, 1), size);
	ad->adjacent[6] = tileAt(tiles, position + Vector2D(0, 1), size);
	ad->adjacent[7] = tileAt(tiles, position + Vector2D(1, 1), size);
	return ad;
}

class MapCompiler {
public:
	void compile(string mapName) {
		vector<string> sceneNames = getSceneNames(mapName);
		Json map = Json::object();
		map["name"] = mapName;
		map["scenes"] = Json::array();
		for (string s : sceneNames) {
			map["scenes"].push_back(compileScene(s, mapName));
		}
		FileSystemHandler h = FileSystemHandler();
		h.saveToFile("maps/" + mapName + "/" + "precompilation.json", map.dump(4));
	}
private:
	vector<string> getSceneNames(string mapName) {
		vector<string> dirs;		
		FileSystemHandler h = FileSystemHandler();
		dirs = h.listDir("maps/" + mapName);
		vector<string> scenes;
		copy_if(dirs.begin(), dirs.end(), std::back_inserter(scenes), [](string i) {
			return !boost::algorithm::contains(i, ".");
		});
		return scenes;
	}

	Json compileScene(string sceneName, string mapName) {
		Json scene = Json::object();
		scene["name"] = sceneName;
		scene["tiles"] = fillLayer(mapName + "/" + sceneName + "/" + "tiles.png", Layer::TILES, dataForTiles);
		scene["objects"] = fillLayer(mapName + "/" + sceneName + "/" + "objects.png", Layer::OBJECTS);
		scene["entities"] = fillLayer(mapName + "/" + sceneName + "/" + "entities.png", Layer::ENTITIES);
		scene["scripts"] = {};
		return scene;
	}

	Tiles buildTiles(string source, Layer layer) {
		string mapBasePath = "maps/";
		Asset* sourceAsset = new Asset(source, mapBasePath);
		Vector2D size = sourceAsset->getImageSize();
		ALLEGRO_BITMAP* image = sourceAsset->getImage();

		Tiles tiles(size.getX(), size.getY());

		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				Color tileColor = Color(al_get_pixel(image, x, y));
				int tileId = DrawDecoder::get()->getTile(tileColor, layer);
				tiles.insert_element(x, y, tileId);
			}
		}

		sourceAsset->onDelete();
		delete(sourceAsset);

		return tiles;
	}

	Json fillLayer(string source, Layer layer, DataCreator fun = nullptr) {
		Tiles tiles = buildTiles(source, layer);
		Json array = Json::array();
		Vector2D size = Vector2D(tiles.size1(), tiles.size2());
		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				int current = tiles(x, y);
				if (current == 0) {
					continue;
				}
				array.push_back(compile(current, tiles, Vector2D(x, y), layer, fun));
			}
		}
		return array;
	}

	Json compile(int current, Tiles tiles, Vector2D pos, Layer layer, DataCreator data) {
		void* ad = nullptr;
		if (data != nullptr) {
			ad = data(tiles, pos);
		}
		return ObjectFactory::get()->compile(current, layer, CreationData(current, pos, ad));		
	}
};