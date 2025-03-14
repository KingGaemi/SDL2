#pragma once

#include "ECS/Component.h"
#include <string>
#include <unordered_set>





class DamageComponent : public Component{

public:
	// isProcessed = false;
	int damage = 1;
	std::string attackType;
	std::unordered_set<std::size_t> hitTargets;

	DamageComponent() {}
	DamageComponent(int damage, std::string attackType) : damage(damage), attackType(attackType) {}
	// AttackComponent(bool isProcessed) : isProcessed(isProcessed) {}


private:

};