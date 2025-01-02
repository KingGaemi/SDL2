#pragma once

#include "ECS/Component.h"





class StatusComponent : public Component {


public:

	bool alive = true;
	int maxHp, 
		maxMp, 
		hp, 
		mp, 
		strength, 
		agility, 
		intelligence, 
		physicalDamage;
	float attackSpeed, movementSpeed;

	//float timeSpeed


	StatusComponent() {

		maxHp = 1;
		maxMp = 1;
		hp = 1;
		mp = 1;
		movementSpeed = 100.0f;
		attackSpeed = 3.0f;   // ms,     can attack (attackSpeed/1000) per one second
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 10;

	}
	StatusComponent(int maxHp, int maxMp) : maxHp(maxHp) , maxMp(maxMp) {
		hp = maxHp;
		mp = maxMp;
		movementSpeed = 200.0f;
		attackSpeed = 3.0f;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 10;
	}


private:


};