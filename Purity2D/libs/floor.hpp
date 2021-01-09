#pragma once

#include "objectCreator.hpp"
#include "meshAdjacent.hpp"
#include "floorShader.hpp"

class Floor : public ObjectCreator {
public:
	Floor() : ObjectCreator(ObjectType::FLOOR, Layer::TILES) {	}

	Json compile(CreationData data) {
		Json j = Json::object();
		j["id"] = data.id;
		j["data"]["position"]["x"] = data.position.getX();
		j["data"]["position"]["y"] = data.position.getY();
		MeshAdjacent* ad = static_cast<MeshAdjacent*>(data.extra);
		vector<ShaderPart> shaders = FloorShader::shade(ad);
		j["data"]["shaders"] = Json::array();
		for (ShaderPart s : shaders) {
			Json shader = Json::object();
			shader["index"] = s.shaderNumber;
			shader["rotation"] = s.shaderRotation;
			j["data"]["shaders"].push_back(shader);
		}
		return j;
	}

	GameObject* load(LoadData data) {
		Json j = data.loadedData;
		GameObject* tile = new GameObject(j["id"]);
		vector<ShaderPart> shaders;
		for (auto& element : j["data"]["shaders"]) {
			shaders.push_back(ShaderPart(element["index"], element["rotation"]));
		}
		Vector2D position = Vector2D(j["data"]["position"]["x"], j["data"]["position"]["y"]);
		MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);

		tile->addComponent(new ImageRenderer());
		tile->addComponent(new Visibility());
		tile->addComponent(new ShaderAsset("floor.jpg", PartitionConfig("SimpleShaders.png", 2, 2), shaders));
		tile->addComponent(new Transform(Vector2D(1, 1), Vector2D::ZERO, Rotation()));
		scene->addGameObject(tile, position, 0);
		return tile;
	}

};