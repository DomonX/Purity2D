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
		cout << "Starting attacks" << endl;
		currentAttacker = attacker;
		currentDefender = defender;
		timePassed = 0;
		hasStopped = false;
		isAttacking = true;
		timeForAttack = calculateTimeForAttack();
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
		cout << "Stopping attacks" << endl;
		if (timePassed * 2 < timeForAttack) {
			isAttacking = false;
			timePassed = 0;
		}
		hasStopped = true;
	}
private:
	void applyAttack() {
		double reduction = calculateReduction();
		currentDefender->currentHealth -= currentAttacker->attackDamage * reduction;
		if (hasStopped) {
			isAttacking = false;
		}
		cout << "Left Health: " << currentDefender->currentHealth << endl;
	}
	double calculateReduction() {
		int armor = currentDefender->armor;
		if (armor < 0) {
			return 2 - (100 / (100 - (double)armor));
		} else {
			return 100 / (100 + (double)armor);
		}
	}
	double calculateTimeForAttack() {
		return 1 / currentAttacker->attackSpeed;
	}
};
