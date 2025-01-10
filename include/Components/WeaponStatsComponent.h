#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

enum class WeaponType{
	Sword,
	Axe,
	Bow,
	Fist
};


class WeaponStatsComponent : public StatsComponent{

public:
	WeaponType weaponType;
	int damage = 0;



};