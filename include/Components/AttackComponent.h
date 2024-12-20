#pragma once

#include "ECS/Component.h"
#include <string>





class AttackComponent : public Component{

public:
	// isProcessed = false;
	int damage = 1;

	AttackComponent() {}
	AttackComponent(int damage) : damage(damage) {}
	// AttackComponent(bool isProcessed) : isProcessed(isProcessed) {}


private:

};