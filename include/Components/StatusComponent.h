#pragma once

#include "ECS/Component.h"





class StatusComponent : public Component {


public:

	bool isAlive = true;
	bool isInvincible = false;
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
		isInvincible = true;
	}
	StatusComponent(int maxHp, int maxMp, float movementSpeed) : maxHp(maxHp) , maxMp(maxMp), movementSpeed(movementSpeed) {
		currentHp = maxHp;
		currentmp = maxMp;
		attackSpeed = 2.0f;
		runningSpeedMultiple = 2.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 10;
	}


private:


};