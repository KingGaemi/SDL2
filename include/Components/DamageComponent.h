#pragma once

#include "ECS/Component.h"
#include <string>
#include <unordered_set>





class DamageComponent : public Component{

public:
	// isProcessed = false;
	int damage = 1;

	std::unordered_set<std::size_t> hitTargets;

	DamageComponent() {}
	DamageComponent(int damage) : damage(damage) {}
	// AttackComponent(bool isProcessed) : isProcessed(isProcessed) {}


private:

};