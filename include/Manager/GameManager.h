#pragma once
#include "Events/EventManager.h"
#include "Groups.h"
#include <memory>


class ECSManager;
class EffectManager;

class GameManager {

public:
	GameManager(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {}
	int currentHour;
	int currentMinute;
	int currentRound;

	std::size_t playerId;
	bool isGameover = false;


	void gameStart();
	void popUpSelectMenu();
	void gameOver(int reason);
	void stageClear();

	void setEventManager(std::shared_ptr<EventManager>& p_eventManager){
		eventManager = p_eventManager;
	}

	SceneCode getCurrentScene();

private:
	std::shared_ptr<ECSManager> ecsManager;
	std::shared_ptr<EventManager> eventManager;
	std::shared_ptr<EffectManager> effectManager;
	SceneCode currentScene;
};