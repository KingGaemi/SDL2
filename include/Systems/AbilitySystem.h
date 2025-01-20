#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"

struct AbilityInform{
	std::string abilityName;
	std::string discription;

	bool isAOE;

};



class AbilitySystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>&entities , float deltaTime) override;
	void init();

};