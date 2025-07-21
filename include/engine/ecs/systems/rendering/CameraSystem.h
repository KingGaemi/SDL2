#pragma once	

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "ecs/ECSManager.h"
class CameraSystem : public System {

public:
	CameraSystem(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<Entity> playerEntity;
	std::shared_ptr<ECSManager> ecsManager;
};