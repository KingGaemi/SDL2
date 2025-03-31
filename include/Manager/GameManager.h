#pragma once
#include "Events/EventManager.h"
#include <memory>

class GameManager {

public:


	int currentHour;
	int currentMinute;
	int currentRound;

	std::size_t playerId;
	bool isGameover = false;


	void gameStart();

	void setEventManager(std::shared_ptr<EventManager>& p_eventManager){
		eventManager = p_eventManager;
	}

private:
	std::shared_ptr<EventManager> eventManager;

};