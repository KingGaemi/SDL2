#pragma once
#include "ECS/System.h"
#include "Events/EventManager.h"



class EventSystem : public System {


public:

	EventSystem(EventManager* eventManager) : eventManager(eventManager) {} 

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void handleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>&entities);



private:
	EventManager* eventManager;
	



};