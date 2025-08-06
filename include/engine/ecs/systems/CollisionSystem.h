#pragma once

#include "engine/ecs/core/Entity.h"
#include "engine/ecs/core/ECSCoordinator.h"
#include "engine/ecs/core/System.h"






class CollisionSystem : public System {	


public:

	CollisionSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}

	void update(float deltaTime) override;
	std::vector<std::shared_ptr<Entity>> getColliders(std::vector<std::shared_ptr<Entity>>& entities);
	std::vector<std::shared_ptr<Entity>> getSolidColliders(std::vector<std::shared_ptr<Entity>>& entities);
	void updateCollidersPosition(std::vector<std::shared_ptr<Entity>>& colliders);
	void updateCollidersRotation(std::vector<std::shared_ptr<Entity>>& colliders);
	void checkCollisions(std::vector<std::shared_ptr<Entity>>& colliders);

	
private:

	std::shared_ptr<ECSManager> ecsManager;

};





