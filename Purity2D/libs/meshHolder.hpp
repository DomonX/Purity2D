#pragma once

#include "component.hpp"
#include "mesh.hpp"
#include "EDirection.hpp"

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

	JsonProperty serialize() {
		JsonProperty data = JsonProperty("position");
		data.value["x"] = position.getX();
		data.value["y"] = position.getY();
		return data;
	}

	Direction getNear(Vector2D pos) {
		Vector2D dif = pos - position;
		if (dif.getX() == 1) {
			return Direction::RIGHT;
		}
		if (dif.getX() == -1) {
			return Direction::LEFT;
		}
		if (dif.getY() == 1) {
			return Direction::DOWN;
		}
		if (dif.getY() == 1) {
			return Direction::UP;
		}
		return Direction::NONE;
	}
};