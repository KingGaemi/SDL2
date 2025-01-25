#pragma once
#include "ECS/System.h"
#include "ECS/Entity.h"

class AISystem : public System{

public:
	void update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime) override;
	void trackTargetsForMissiles(std::shared_ptr<Entity>& entity);
	bool findTarget(std::vector<std::shared_ptr<Entity>>&entities, std::shared_ptr<Entity>& missile);
};	