#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Events/EventManager.h"







class CommandSystem : public System {

public:
	CommandSystem(std::shared_ptr<EventManager>& eventManager): eventManager(eventManager) {}
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;



private:
	std::shared_ptr<EventManager> eventManager;
};