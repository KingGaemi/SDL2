#pragma once
#include "ECS/System.h"
#include "Events/EventManager.h"
#include "KeyCode.h"
#include <type_traits>



class EventSystem : public System {


public:

	EventSystem(EventManager* eventManager) : eventManager(eventManager) { 
		
		std::fill_n(pressed, toInt(KeyCode::NUM_OF_KEY_CODES), false);
	}  

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void handleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>&entities);

	bool isControl(const KeyCode& key);
	bool isArrow(const KeyCode& key);
	bool isHorizontal(const KeyCode& key);
	bool isVertical(const KeyCode& key);
	bool isAttack(const KeyCode& key);

private:
	EventManager* eventManager;
	bool pressed[toInt(KeyCode::NUM_OF_KEY_CODES)]; 
		
	KeyCode lastHorizontalKey = KeyCode::Unknown;
	KeyCode lastVerticalKey = KeyCode::Unknown;
	KeyCode lastArrowKey = KeyCode::Unknown;


};