#pragma once

#include "entity.hpp"
#include "time.hpp"

class BattleService {
private:
	Entity* currentAttacker;
	Entity* currentDefender;
	double timePassed = 0;
	double timeForAttack = 0;
	bool hasStopped = false;
	bool isAttacking = false;
public:
	void attack(Entity* attacker, Entity* defender) {
		currentAttacker = attacker;
		currentDefender = defender;
		timePassed = 0;
		hasStopped = false;
		isAttacking = true;
		calculateTimeForAttack();
	}

	void onUpdate() {
		if (!isAttacking) {
			return;
		}
		timePassed += Time::getDeltaTime();
		if (timePassed >= timeForAttack) {
			applyAttack();
			timePassed -= timeForAttack;
			timeForAttack = calculateTimeForAttack();
		}
	}

	void stopAttacks() {
		hasStopped = true;
	}
private:
	void applyAttack() {
		double reduction = calculateReduction();
		currentDefender->currentHealth -= currentAttacker->attackDamage * reduction;
		if (hasStopped) {
			isAttacking = false;
		}
	}
	double calculateReduction() {
		int armor = currentDefender->armor;
		if (armor < 0) {
			return 2 - (100 / (100 - armor));
		} else {
			return 100 / (100 + armor);
		}
	}
	double calculateTimeForAttack() {
		return 1000 / currentAttacker->attackSpeed;
	}
};
