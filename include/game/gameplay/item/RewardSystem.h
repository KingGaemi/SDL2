#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/ECSCoordinator.h"
#include "engine/ecs/core/ECSCoordinator.h"


class RewardSystem : public System {

public:
	RewardSystem(std::shared_ptr<ECSManager> ecsManager, std::shared_ptr<EventManager> eventManager) : eventManager(eventManager) {}


	void update(float deltaTime) override;

private:
	std::shared_ptr<ECSManager> ecsManager;
	std::shared_ptr<EventManager> eventManager;

};