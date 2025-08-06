#pragma once	

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include "engine/ecs/core/ECSCoordinator.h"
class CameraSystem : public System {

public:
	CameraSystem(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {}
	void update(float deltaTime) override;

private:
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<Entity> playerEntity;
	std::shared_ptr<ECSManager> ecsManager;
};