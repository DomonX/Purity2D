#pragma once

class ShaderPart {
public:
	short shaderNumber;
	short shaderRotation;

	ShaderPart(short shaderNumber, short shaderRotation) {
		this->shaderNumber = shaderNumber;
		this->shaderRotation = shaderRotation;
	}
};