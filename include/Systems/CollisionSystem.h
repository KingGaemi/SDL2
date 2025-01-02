#pragma once

#include "ECS/Entity.h"
#include "ECS/ECSManager.h"
#include "ECS/System.h"
#include "Components/ColliderComponent.h"





class CollisionSystem : public System {	


public:

	CollisionSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	bool static AABB(const Rect& recA , const Rect& recB);

	bool static AABB(const ColliderComponent& colA , const ColliderComponent& colB);
	
private:

	std::shared_ptr<ECSManager> ecsManager;

};





