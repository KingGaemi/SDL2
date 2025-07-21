#pragma once

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "Events/EventManager.h"







class CommandSystem : public System {

public:
	CommandSystem(std::shared_ptr<EventManager>& eventManager): eventManager(eventManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;



private:
	std::shared_ptr<EventManager> eventManager;
};