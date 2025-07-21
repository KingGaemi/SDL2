#pragma once
#include "ecs/System.h"
#include "Events/EventManager.h"
#include "engine/input/KeyCode.h"
// #include <type_traits>



class MiddleEventSystem : public System {


public:

	MiddleEventSystem(std::shared_ptr<EventManager>& eventManager) : eventManager(eventManager) { 		
		// std::fill_n(pressed, toInt(KeyCode::NUM_OF_KEY_CODES), false);
	}  

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void handleMiddleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>&entities);


private:
	std::shared_ptr<EventManager> eventManager;
	std::shared_ptr<Entity> player1;
	std::shared_ptr<Entity> player2;
};