#pragma once

#include "ecs/Entity.h"
#include "ecs/System.h"
#include "ecs/ECSManager.h"

class CollisionEventHandlerSystem : public System {


public:
	CollisionEventHandlerSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
	void applyRoot(std::shared_ptr<Entity> charactor, std::shared_ptr<Entity> item);
private:
	std::shared_ptr<ECSManager> ecsManager;
};






