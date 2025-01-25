#pragma once

#include "ECS/Component.h"





class StatusComponent : public Component {


public:

	bool alive = true;
	bool invincible = false;
	int maxHp, 
		maxMp, 
		currentHp, 
		currentmp, 
		strength, 
		agility, 
		intelligence, 
		physicalDamage;
	float attackSpeed, movementSpeed, runningSpeedMultiple;
	float projectileSpeedMultiple = 1.0f;

	//float timeSpeed

	StatusComponent() {
		maxHp = 1;
		maxMp = 1;
		currentHp = 1;
		currentmp = 1;
		movementSpeed = 0.0f;
		attackSpeed = 1.0f;   // ms,     can attack (attackSpeed/1000) per one second
		runningSpeedMultiple = 2.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 1;
		invincible = true;
	}
	StatusComponent(int maxHp, int maxMp) : maxHp(maxHp) , maxMp(maxMp) {
		currentHp = maxHp;
		currentmp = maxMp;
		movementSpeed = 200.0f;
		attackSpeed = 2.0f;
		runningSpeedMultiple = 2.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 1;
	}


private:


};