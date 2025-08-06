#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include "engine/event/EventManager.h"







class CommandSystem : public System {

public:
	CommandSystem(std::shared_ptr<EventManager>& eventManager): eventManager(eventManager) {}
	void update(float deltaTime) override;



private:
	std::shared_ptr<EventManager> eventManager;
};