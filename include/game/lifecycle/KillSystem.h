#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include "Manager/GameManager.h"

class KillSystem : public System{

public:

	
	KillSystem(std::shared_ptr<GameManager>& gameManager) : gameManager(gameManager){}
	void update(float deltaTime) override;

private:
	std::shared_ptr<GameManager> gameManager;
};