#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/ecs/core/Entity.h"

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