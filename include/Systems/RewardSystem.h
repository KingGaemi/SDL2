#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "ECS/ECSManager.h"


class RewardSystem : public System {

public:
	RewardSystem(std::shared_ptr<ECSManager> ecsManager, std::shared_ptr<EventManager> eventManager) : eventManager(eventManager) {}


	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:
	std::shared_ptr<ECSManager> ecsManager;
	std::shared_ptr<EventManager> eventManager;

};