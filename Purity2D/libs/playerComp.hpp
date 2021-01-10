#pragma once

#include "entity.hpp"
#include "battleService.hpp"

class PlayerComponent : public Entity {
private:
	MeshHolder* mesh;
	BattleService battlerService;
	GameObject* currentAttackedEntity;
	bool isAttacking = false;
public:
	PlayerComponent(Scene* scene, int health, double attackSpeed, int attackDamage, int armor) : Entity(scene, health, attackSpeed, attackDamage, armor) {	}
	void entitySelected(GameObject* entity) {
		if (currentAttackedEntity == entity) {
			currentAttackedEntity = nullptr;
			cout << "enemy unselected" << endl;
		} else {
			cout << "enemy selected" << endl;
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
		bool isNear = mesh->getNear(this->mesh->getPosition());
		if (isNear && !isAttacking) {
			isAttacking = true;
			Entity* e = currentAttackedEntity->getComponent<Entity>();
			battlerService.attack(this, e);
		}
		else if (!isNear && isAttacking) {
			isAttacking = false;
			battlerService.stopAttacks();
		}
	}
};