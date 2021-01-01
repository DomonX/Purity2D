#pragma once

#include "shaderAsset.h"
#include "meshLoader.hpp"
#include "objectFactory.hpp"

class WallShader {
public:
	static vector<ShaderPart> shade(MeshAdjacent* tiles) {
		ObjectFactory* fc = ObjectFactory::get();
		MeshAdjacent types;
		vector<ShaderPart> parts;
		for (int i = 0; i < 8; i++) {
			types.adjacent[i] = (int)fc->type(tiles->adjacent[i], Layer::TILES);
		}

		if (types.adjacent[3] == (int)ObjectType::WALL && types.adjacent[6] == (int)ObjectType::WALL) {
			int corner = getCornerType(types.adjacent[5]);
			if (corner != -1) {
				parts.push_back(ShaderPart(corner, 2));
			}
		}

		if (types.adjacent[1] == (int)ObjectType::WALL && types.adjacent[3] == (int)ObjectType::WALL) {
			int corner = getCornerType(types.adjacent[0]);
			if (corner != -1) {
				parts.push_back(ShaderPart(corner, 3));
			}
		}

		if (types.adjacent[1] == (int)ObjectType::WALL && types.adjacent[4] == (int)ObjectType::WALL) {
			int corner = getCornerType(types.adjacent[2]);
			if (corner != -1) {
				parts.push_back(ShaderPart(corner, 0));
			}
		}

		if (types.adjacent[4] == (int)ObjectType::WALL && types.adjacent[6] == (int)ObjectType::WALL) {
			int corner = getCornerType(types.adjacent[7]);
			if (corner != -1) {
				parts.push_back(ShaderPart(corner, 1));
			}
		}

		int sideType = getSideType(types.adjacent[1]);
		if (sideType != -1) {
			parts.push_back(ShaderPart(sideType, 3));
		}

		sideType = getSideType(types.adjacent[4]);
		if (sideType != -1) {
			parts.push_back(ShaderPart(sideType, 0));
		}

		sideType = getSideType(types.adjacent[6]);
		if (sideType != -1) {
			parts.push_back(ShaderPart(sideType, 1));
		}

		sideType = getSideType(types.adjacent[3]);
		if (sideType != -1) {
			parts.push_back(ShaderPart(sideType, 2));
		}

		return parts;
	}
private:
	static int getCornerType(int type) {
		if (type == (int)ObjectType::FLOOR) {
			return 3;
		}
		if (type == (int)ObjectType::UNKNOWN) {
			return 2;
		}
		return -1;
	}

	static int getSideType(int type) {
		if (type == (int)ObjectType::FLOOR) {
			return 1;
		}
		if (type == (int)ObjectType::UNKNOWN) {
			return 0;
		}
		return -1;
	}
};