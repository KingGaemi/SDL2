#pragma once

#include "ecs/System.h"
#include "ecs/ECSManager.h"
#include "ecs/ECSManager.h"


class RewardSystem : public System {

public:
	RewardSystem(std::shared_ptr<ECSManager> ecsManager, std::shared_ptr<EventManager> eventManager) : eventManager(eventManager) {}


	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:
	std::shared_ptr<ECSManager> ecsManager;
	std::shared_ptr<EventManager> eventManager;

};