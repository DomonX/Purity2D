#pragma once

#include "entity.hpp"
#include "battleService.hpp"

class PlayerComponent : public Entity {
private:
	MeshHolder* mesh;
	BattleService battlerService;
	GameObject* currentAttackedEntity;
public:
	PlayerComponent(Scene* scene, int health, double attackSpeed, int attackDamage, int armor) : Entity(scene, health, attackSpeed, attackDamage, armor) {	}
	void entitySelected(GameObject* entity) {
		if (currentAttackedEntity == entity) {
			currentAttackedEntity = nullptr;
		} else {
			currentAttackedEntity = entity;
		}
	}

	void onGetOtherComponent(Component* component) {
		Entity::storeIfIsInstance(&mesh, component);
	}

	void onUpdate() {
		if (!currentAttackedEntity) {
			return;
		}
		battlerService.onUpdate();
		MeshHolder* mesh = currentAttackedEntity->getComponent<MeshHolder>();
		if (mesh->getNear(this->mesh->getPosition()) != Direction::NONE) {
			Entity* e = currentAttackedEntity->getComponent<Entity>();
			battlerService.attack(this, e);
		} else {
			battlerService.stopAttacks();
		}
	}
};