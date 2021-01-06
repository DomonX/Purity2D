#pragma once

#include <vector>

#include "shaderPart.hpp"
#include "meshAdjacent.hpp"

using namespace std;

class ShaderBuilder {
public:
	virtual vector<ShaderPart> shade(MeshAdjacent adjactent) {	return {};	}
};