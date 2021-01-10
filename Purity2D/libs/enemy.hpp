#pragma once

#include "objectCreator.hpp"
#include "imageRenderer.hpp"
#include "visibility.hpp"
#include "meshCollider.hpp"
#include "meshController.hpp"
#include "sprite.hpp"
#include "meshAi.hpp"
#include "animator.hpp"
#include "enemyCmp.hpp"

class Enemy : public ObjectCreator {
public:
	Enemy() : ObjectCreator(ObjectType::UNKNOWN, Layer::ENTITIES) {	}

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
		GameObject* enemy = new GameObject(j["id"]);
		MeshScene* scene = dynamic_cast<MeshScene*>(data.scene);
		enemy->addComponent(new Transform(Vector2D(0.65, 0.75), Vector2D::ZERO, Rotation(0)));
		enemy->addComponent(new ImageRenderer());
		enemy->addComponent(new Visibility());
		Colliders colliders = { { true, true, true, true, false, false, false, false } };
		enemy->addComponent(new MeshCollider(colliders));
		enemy->addComponent(new Sprite("goblin.png", 4, 4));
		enemy->addComponent(new MeshController(3));
		enemy->addComponent(new MeshAi(scene, 6));
		enemy->addComponent(getTypicalAnimator());
		Component* e = dynamic_cast<Component*>(new EnemyComponent(scene, 100, 1.2, 10, 5));
		enemy->addComponent(e);
		scene->addGameObject(enemy, position, 2);
		return enemy;
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