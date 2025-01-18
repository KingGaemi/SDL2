#pragma once	

#include "ECS/System.h"
#include "ECS/Entity.h"

class CameraSystem : public System {

public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<Entity> playerEntity;
};