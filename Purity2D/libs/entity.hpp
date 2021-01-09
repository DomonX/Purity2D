#pragma once

#include "component.hpp"
#include "meshScene.hpp"

class Entity : public Component {
public:
	int maxHealth;
	int currentHealth;
	double attackSpeed;
	int attackDamage;
	int armor;
protected:
	MeshScene* scene;
	MeshHolder* mesh;
public:
	Entity(Scene* scene, int health, double attackSpeed, int attackDamage, int armor) {
		this->currentHealth = health;
		this->maxHealth = health;
		this->attackSpeed = attackSpeed;
		this->attackDamage = attackDamage;
		this->armor = armor;
		this->scene = dynamic_cast<MeshScene*>(scene);
	}

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&mesh, component);
	}
};