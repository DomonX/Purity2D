#pragma once

#include "entity.hpp"
#include "mouseElement.hpp"
#include "playerComp.hpp"
#include "battleService.hpp"

class EnemyComponent : public Entity {
private:
	MeshHolder* mesh;
	Transform* transform;
	BattleService battlerService;
	GameObject* go;
	MouseElement* mouseElement;
public:
	EnemyComponent(Scene* scene, int health, double attackSpeed, int attackDamage, int armor) : Entity(scene, health, attackSpeed, attackDamage, armor) { 
		mouseElement = new MouseElement();
	}

	void setScene(string sceneName) {
		mouseElement->setScene(sceneName);
	}

	void onStart() {
		//mouseElement->onStart();
		mouseElement->connectTransform(transform);
		mouseElement->connectOwner(this);
		mouseElement->onClick = [](Component* current, ClickType click) {
			EnemyComponent* cur = dynamic_cast<EnemyComponent*>(current);
			GameObject* player = (*cur->scene->getPlayer());
			PlayerComponent* p = player->getComponent<PlayerComponent>();
			p->entitySelected(cur->getGo());
		};

	}

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&mesh, component);
		storeIfIsInstance(&transform, component);
	}

	void onUpdate() {
		battlerService.onUpdate();
		GameObject* player = (*scene->getPlayer());
		MeshHolder* mesh = player->getComponent<MeshHolder>();
		if (mesh->getNear(this->mesh->getPosition()) != Direction::NONE) {
			PlayerComponent* p = player->getComponent<PlayerComponent>();
			battlerService.attack(this, p);
		} else {
			battlerService.stopAttacks();
		}
	}

	GameObject* getGo() {
		return go;
	}

	void getGameObject(GameObject* go) {
		this->go = go;
	}

	void onDelete() {
		mouseElement->onDelete();
		delete(mouseElement);
	}
};