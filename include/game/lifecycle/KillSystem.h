#pragma once

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "Manager/GameManager.h"

class KillSystem : public System{

public:

	
	KillSystem(std::shared_ptr<GameManager>& gameManager) : gameManager(gameManager){}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:
	std::shared_ptr<GameManager> gameManager;
};