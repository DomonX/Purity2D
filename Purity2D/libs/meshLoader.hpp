#pragma once

#include "asset.hpp"
#include "meshScene.hpp"
#include "assetManager.hpp"
#include "drawDecoder.hpp"
#include "objectFactory.hpp"
#include "meshAdjacent.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include <string>


using namespace std;

typedef boost::numeric::ublas::matrix<int> Tiles;
typedef void* (*DataCreator)(Tiles, Vector2D, MeshScene*);
typedef void (*PostHandler)(Tiles, Vector2D, MeshScene*, GameObject*);

int tileAt(Tiles tiles, Vector2D pos, Vector2D size) {
	if (pos.getX() < 0 || pos.getY() < 0) {
		return 0;
	}
	if (pos.getX() > size.getX() - 1 || pos.getY() > size.getY() - 1) {
		return 0;
	}
	return tiles(pos.getX(), pos.getY());
}

void* dataForTiles(Tiles tiles, Vector2D position, MeshScene* scene) {
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

void dataForEntites(Tiles tiles, Vector2D position, MeshScene* scene, GameObject* go) {
	int tile = tileAt(tiles, position, Vector2D(tiles.size1(), tiles.size2()));
	ObjectType type = ObjectFactory::get()->type(tile, Layer::ENTITIES);
	if (type == ObjectType::PLAYER) {
		scene->setPlayer(go);
	}
}

class MeshLoader {
public:
	void load(MeshScene* scene, string source) {
		create(scene, source);
	}

	void create(MeshScene* scene, string source) {
		fillLayer(scene, source + "1.png", Layer::TILES, nullptr, dataForTiles);
		fillLayer(scene, source + "2.png", Layer::OBJECTS);
		fillLayer(scene, source + "3.png", Layer::ENTITIES, dataForEntites);
	}

	void fillLayer(MeshScene* scene, string source, Layer layer, PostHandler goFun = nullptr, DataCreator fun = nullptr) {
		Tiles tiles = buildTiles(source, layer);
		Vector2D size = Vector2D(tiles.size1(), tiles.size2());
		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				GameObject* go = create(tiles, Vector2D(x, y), layer, scene, goFun, fun);
			}
		}
	}

protected:
	GameObject* create(Tiles tiles, Vector2D pos, Layer layer, MeshScene* scene, PostHandler post, DataCreator data) {
		int current = tiles(pos.getX(), pos.getY());
		void* ad = nullptr;
		if (data != nullptr) {
			ad = data(tiles, pos, scene);
		}
		GameObject* result = ObjectFactory::get()->create(current, layer, CreationData(current, scene, pos, ad));
		if (post != nullptr) {
			post(tiles, pos, scene, result);
		}
		return result;
	}

	Tiles buildTiles(string source, Layer layer) {
		Asset* sourceAsset = new Asset(source);
		Vector2D size = sourceAsset->getImageSize();
		ALLEGRO_BITMAP* image = sourceAsset->getImage();

		Tiles tiles(size.getX(), size.getY());

		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				tiles.insert_element(x, y, DrawDecoder::get()->getTile(alColorToColor(al_get_pixel(image, x, y)), layer));
			}
		}

		sourceAsset->onDelete();
		delete(sourceAsset);

		return tiles;
	}

private:

	bool comparePixels(Color color1, Color color2) {
		return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
	}

	Color alColorToColor(ALLEGRO_COLOR color) {
		unsigned char r, g, b;
		al_unmap_rgb(color, &r, &g, &b);
		return { r,g,b };
	}
};