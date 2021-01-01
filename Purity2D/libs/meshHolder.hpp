#pragma once

#include "component.hpp"
#include "mesh.hpp"

class MeshHolder : public Component {
private:
	Mesh** hook;
	Vector2D position;
	GameObject* parent = nullptr;
	int layer = -1;
public:
	MeshHolder(Mesh** mesh, Vector2D position, int layer) {
		this->hook = mesh;
		this->position = position;
		this->layer = layer;
	}

	Mesh* getMesh() {
		return *hook;
	}

	void move(Vector2D position) {
		(*hook)->move(parent, this->position, position, layer);
		this->position = position;
	}

	Vector2D getPosition() {
		return position;
	}

	void getGameObject(Component* go) {
		storeIfIsInstance(&parent, go);
	}
};