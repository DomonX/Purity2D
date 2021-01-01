#pragma once

#include "asset.hpp"
#include "meshScene.hpp"
#include "assetManager.hpp"
#include "drawDecoder.hpp"
#include "objectFactory.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include <string>


using namespace std;

struct Tile {
	int type;
	vector<ShaderPart> shader;
	Tile() {
		this->type = 0;
	}

	Tile(int type) {
		this->type = type;
	}
};

class MeshAdjacent {
public:
	int adjacent[8];
};

class MeshLoader {
public:
	void load(MeshScene* scene, string source) {
		create(scene, source);
	}

	void create(MeshScene* scene, string source) {
		Asset* sourceAsset = new Asset(source);
		Vector2D size = sourceAsset->getImageSize();
		ALLEGRO_BITMAP* image = sourceAsset->getImage();

		using namespace boost::numeric::ublas;

		matrix<Tile> tiles(size.getX(), size.getY());

		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				tiles.insert_element(x, y, Tile(DrawDecoder::get()->getTile(alColorToColor(al_get_pixel(image, x, y)))));
			}
		}

		for (int x = 0; x < size.getX(); x++) {
			for (int y = 0; y < size.getY(); y++) {
				Tile current = tiles(x, y);
				MeshAdjacent ad = buildAdjacentTiles(tiles, x, y, size);
				GameObject* go = ObjectFactory::get()->create(current.type, Layer::TILES, CreationData({scene, Vector2D(x,y), &ad}));
			}
		}
	}

	void createSecondLayer(MeshScene* scene, string source) {

	}


private:

	MeshAdjacent buildAdjacentTiles(boost::numeric::ublas::matrix<Tile> tiles, int x, int y, Vector2D size) {
		MeshAdjacent ad = MeshAdjacent();
		ad.adjacent[0] = tileAt(tiles, x - 1, y - 1, size);
		ad.adjacent[1] = tileAt(tiles, x, y - 1, size);
		ad.adjacent[2] = tileAt(tiles, x + 1, y - 1, size);
		ad.adjacent[3] = tileAt(tiles, x - 1, y, size);
		ad.adjacent[4] = tileAt(tiles, x + 1, y, size);
		ad.adjacent[5] = tileAt(tiles, x - 1, y + 1, size);
		ad.adjacent[6] = tileAt(tiles, x, y + 1, size);
		ad.adjacent[7] = tileAt(tiles, x + 1, y + 1, size);
		return ad;
	}

	int tileAt(boost::numeric::ublas::matrix<Tile> tiles, int x, int y, Vector2D size) {
		if (x < 0 || y < 0) {
			return 0;
		}
		if (x > size.getX() - 1 || y > size.getY() - 1) {
			return 0;
		}
		return tiles(x, y).type;
	}

	bool comparePixels(Color color1, Color color2) {
		return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
	}

	Color alColorToColor(ALLEGRO_COLOR color) {
		unsigned char r, g, b;
		al_unmap_rgb(color, &r, &g, &b);
		return { r,g,b };
	}
};