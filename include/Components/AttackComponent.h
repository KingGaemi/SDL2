#pragma once

#include "ECS/Component.h"
#include <string>
#include <unordered_set>





class AttackComponent : public Component{

public:
	// isProcessed = false;
	int damage = 1;

	std::unordered_set<EntityID> hitTargets;

	AttackComponent() {}
	AttackComponent(int damage) : damage(damage) {}
	// AttackComponent(bool isProcessed) : isProcessed(isProcessed) {}


private:

};