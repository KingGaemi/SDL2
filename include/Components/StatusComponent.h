#pragma once

#include "ECS/Component.h"





class StatusComponent : public Component {


public:

	int maxHp, 
		maxMp, 
		hp, 
		mp, 
		movementSpeed, 
		attackSpeed, 
		strength, 
		agility, 
		intelligence, 
		physicalDamage;


	//float timeSpeed


	StatusComponent() {

		maxHp = 1;
		maxMp = 1;
		hp = 1;
		mp = 1;
		movementSpeed = 5;
		attackSpeed = 1;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 1;

	}
	StatusComponent(int maxHp, int maxMp) : maxHp(maxHp) , maxMp(maxMp) {
		hp = maxHp;
		mp = maxMp;
		movementSpeed = 100;
		attackSpeed = 1;
		strength = 1;
		agility = 1;
		intelligence = 1;
		physicalDamage = 1;
	}


private:


};