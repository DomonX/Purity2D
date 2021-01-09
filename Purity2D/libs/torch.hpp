#pragma once

#include "objectCreator.hpp"
#include "lightRenderer.hpp"

class Torch : public ObjectCreator {
public:
	Torch() : ObjectCreator(ObjectType::UNKNOWN, Layer::OBJECTS) {	}

	Json compile(CreationData data) {
		Json j = Json::object();
		j["id"] = data.id;
		j["data"]["position"]["x"] = data.position.getX();
		j["data"]["position"]["y"] = data.position.getY();
		return j;
	}

	GameObject* load(LoadData data) {
		Json j = data.loadedData;
		Vector2D position = Vector2D(j["data"]["position"]["x"], j["data"]["position"]["y"]);

		GameObject* torch = new GameObject(j["id"]);
		torch->addComponent(new ImageRenderer());
		torch->addComponent(new Visibility());
		torch->addComponent(new Asset("torch.png"));
		torch->addComponent(new Transform(Vector2D(0.5, 0.5), Vector2D::ZERO, Rotation()));
		MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
		scene->addGameObject(torch, position, 1);
		GameObject* light = new GameObject(0);
		light->addComponent(new Transform(Vector2D(40, 40), scene->calculatePosition(position), Rotation()));
		light->addComponent(new LightRenderer());
		light->addComponent(new Asset("light.png"));
		scene->addLight(light);
		return torch;
	}

};