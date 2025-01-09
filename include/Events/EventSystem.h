#pragma once
#include "ECS/System.h"
#include "Events/EventManager.h"
#include "Components/DirectionComponent.h"
#include "KeyCode.h"
#include <type_traits>



class EventSystem : public System {


public:

	EventSystem(EventManager* eventManager) : eventManager(eventManager) { 
		
		std::fill_n(pressed, toInt(KeyCode::NUM_OF_KEY_CODES), false);
	}  

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void handleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>&entities);

	// bool isControl(const KeyCode& key);
	bool isArrowKey(const KeyCode& key);
	bool isAbilityKey(const KeyCode& key);
	bool isHorizontal(const KeyCode& key);
	bool isVertical(const KeyCode& key);
	bool isAttack(const KeyCode& key);
	bool checkArrowKeyDoubleTapped(const Event& evt);
	bool checkAbilityKeyDoubleTapped(const Event& evt);
	bool arrowIsPressed();
	Direction getDirection(const Event& evt);

private:
	EventManager* eventManager;
	bool pressed[toInt(KeyCode::NUM_OF_KEY_CODES)]; 
	bool isArrowKeyDoubleTapped = false;
	bool isAbilityKeyDoubleTapped = false;
	KeyCode lastHorizontalKey = KeyCode::Unknown;
	KeyCode lastVerticalKey = KeyCode::Unknown;
	KeyCode lastArrowKey = KeyCode::Down;
	KeyCode lastAbilityKey = KeyCode::Unknown;
	float doubleTapTime = 0.17; // sec
	float leftDoubleTapTime = 0;
	Direction direction = {0, 0};

	std::shared_ptr<Entity> targetEntity;

};