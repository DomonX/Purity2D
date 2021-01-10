#pragma once

#include "entity.hpp"
#include "mouseElement.hpp"
#include "playerComp.hpp"
#include "battleService.hpp"

class EnemyComponent : public Entity {
private:
	MeshHolder* mesh;
	Transform* transform;
	BattleService* battlerService;
	GameObject* go;
	MouseElement* mouseElement;
	bool isAttacking = false;
public:
	EnemyComponent(Scene* scene, int health, double attackSpeed, int attackDamage, int armor) : Entity(scene, health, attackSpeed, attackDamage, armor) { 
		mouseElement = new MouseElement();
		battlerService = new BattleService();
	}

	void setScene(string sceneName) {
		mouseElement->setScene(sceneName);
	}

	void onStart() {
		mouseElement->onStart();
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
		if(currentHealth <= 0) {
			scene->removeGameObject(mesh->getPosition(), (int)Layer::ENTITIES);
			return;
		}
		battlerService->onUpdate();
		GameObject* player = (*scene->getPlayer());
		MeshHolder* mesh = player->getComponent<MeshHolder>();
		bool isNear = mesh->getNear(this->mesh->getPosition());
		if (isNear && !isAttacking) {
			isAttacking = true;
			PlayerComponent* p = player->getComponent<PlayerComponent>();
			battlerService->attack(this, p);
		} else if(!isNear && isAttacking){
			isAttacking = false;
			battlerService->stopAttacks();
		}
	}

	GameObject* getGo() {
		return go;
	}

	void getGameObject(Component* go) {
		this->go = dynamic_cast<GameObject*>(go);
	}

	void onDelete() {
		GameObject* player = (*scene->getPlayer());
		PlayerComponent* p = player->getComponent<PlayerComponent>();
		p->entitySelected(nullptr);
		mouseElement->onDelete();
		delete(mouseElement);
		delete(battlerService);
	}
};