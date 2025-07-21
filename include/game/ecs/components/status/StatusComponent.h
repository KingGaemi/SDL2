#pragma once

#include "engine/ecs/core/Component.h"





class StatusComponent : public Component {


public:

	bool isAlive = true;
	bool isInvincible = false;
	bool damagedRecently = false;
	int maxHp, 
		maxMp, 
		currentHp, 
		currentmp, 
		strength, 
		agility, 
		intelligence, 
		physicalDamage,
		recentDamage;
	float attackSpeed, movementSpeed, runningSpeedMultiple;
	float percentage; // 1 => 100% , 0.1 => 10%
	float baseAttackSpeed = 1.0f;
	float projectileSpeedMultiple = 1.0f;
	float timer = 0.0f;
	float recentTime = 3.0;
	int exp = 0;
	int rewardExp = 50;
	int level = 1;
	int maxLevel = 99;
	float range = 3000.0f;
	float agilPerLv = 1.0f;
	float strPerLv = 1.0f;
	float intPerLv = 1.0f;
	std::vector<int> xpTable = {0, 100, 250, 500, 1000, 2000};
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
	StatusComponent(int maxHp, int maxMp, float attackSpeed, float movementSpeed) : maxHp(maxHp), maxMp(maxMp), attackSpeed(attackSpeed), movementSpeed(movementSpeed) {
		currentHp = maxHp;
		currentmp = maxMp;
		runningSpeedMultiple = 2.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 10;
		recentDamage = 0;
		percentage = currentHp/maxHp;
	}
		
	StatusComponent(int maxHp, int maxMp, float attackSpeed, float movementSpeed, int physicalDamage) : maxHp(maxHp), maxMp(maxMp), physicalDamage(physicalDamage), attackSpeed(attackSpeed), movementSpeed(movementSpeed)  {
		currentHp = maxHp;
		currentmp = maxMp;
		runningSpeedMultiple = 2.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		recentDamage = 0;
		percentage = currentHp/maxHp;
	}

	void gainExp(int expGain){
		exp += expGain;

		if(exp > xpTable[level]){
			exp -= xpTable[level++];
			std::cout << "Level up!!" << std::endl;
		}

		std::cout << "level : "<< level << std::endl;
		std::cout << "exp : "<< exp << std::endl;
	}

	void takeDamage(int amount){
		currentHp -= amount;
        recentDamage += amount;
        damagedRecently = true;
        timer = recentTime;
	}

private:


};