#pragma once

#include "engine/ecs/core/Entity.h"
#include "engine/ecs/core/System.h"
#include "engine/ecs/core/ECSCoordinator.h"

class CollisionEventHandlerSystem : public System {


public:
	CollisionEventHandlerSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}
	void update(float deltaTime) override;
	void applyRoot(std::shared_ptr<Entity> charactor, std::shared_ptr<Entity> item);
private:
	std::shared_ptr<ECSManager> ecsManager;
};






