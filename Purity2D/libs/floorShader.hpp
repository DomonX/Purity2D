#pragma once


#include "shaderAsset.h"
#include "objectFactory.hpp"

class FloorShader {
public:
	static vector<ShaderPart> shade(MeshAdjacent* tiles) {
		ObjectFactory* fc = ObjectFactory::get();
		MeshAdjacent types;
		vector<ShaderPart> parts;
		for (int i = 0; i < 8; i++) {
			types.adjacent[i] = (int)fc->type(tiles->adjacent[i], Layer::TILES);
		}
		if (types.adjacent[4] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(1, 0));
		}
		if (types.adjacent[6] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(1, 1));
		}
		if (types.adjacent[3] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(1, 2));
		}
		if (types.adjacent[1] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(1, 3));
		}
		if (types.adjacent[2] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(3, 0));
		}
		if (types.adjacent[7] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(3, 1));
		}
		if (types.adjacent[5] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(3, 2));
		}
		if (types.adjacent[0] == (int)ObjectType::WALL) {
			parts.push_back(ShaderPart(3, 3));
		}
		return parts;
	}
};