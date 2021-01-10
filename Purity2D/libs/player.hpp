#pragma once

#include "objectCreator.hpp"
#include "PlayerMovement.hpp"
#include "playerComp.hpp"

class Player : public ObjectCreator {
public:
	Player() : ObjectCreator(ObjectType::PLAYER, Layer::ENTITIES) {	}

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
		GameObject* player = new GameObject(j["id"]);
		Camera* cam = data.scene->getCamera();
		player->addComponent(new Transform(Vector2D(0.60, 0.75), Vector2D::ZERO, Rotation(0)));
		player->addComponent(new ImageRenderer());
		player->addComponent(new Visibility());
		Colliders colliders = { { true, true, true, true, false, false, false, false } };
		player->addComponent(new MeshCollider(colliders));
		player->addComponent(new Sprite("player.png", 4, 4));
		player->addComponent(new MeshController(3));
		player->addComponent(new PlayerMovement());
		player->addComponent(new PlayerComponent(data.scene, 170, 0.7, 12, 19));
		player->addComponent(getTypicalAnimator());
		player->addGameObject(cam);
		MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
		scene->addGameObject(player, position, 2);
		return player;
	}
private:
	Animator* getTypicalAnimator() {
		vector<Vector2D> goDown = { Vector2D(1, 0), Vector2D(2, 0), Vector2D(3, 0), Vector2D(0, 0) };
		vector<Vector2D> goLeft = { Vector2D(1, 1), Vector2D(2, 1), Vector2D(3, 1), Vector2D(0, 1) };
		vector<Vector2D> goRight = { Vector2D(1, 2), Vector2D(2, 2), Vector2D(3, 2), Vector2D(0, 2) };
		vector<Vector2D> goUp = { Vector2D(1, 3), Vector2D(2, 3), Vector2D(3, 3), Vector2D(0, 3) };
		map<string, vector<Vector2D>> anims = { {"goDown", goDown }, {"goLeft", goLeft }, {"goRight", goRight }, {"goUp", goUp }, };
		return new Animator(anims);
	}

};