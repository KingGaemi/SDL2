#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/ECSManager.h"

#include "Components/TransformComponent.h"
#include "Components/AttackComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/LifeTimeComponent.h"




class AttackSystem : public System {


public:
	AttackSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:

	std::shared_ptr<ECSManager> ecsManager;
};






