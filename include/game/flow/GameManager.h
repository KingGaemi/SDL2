#pragma once
#include "engine/event/EventManager.h"
#include "game/gameplay/spawn/SpawnManager.h"
#include "game/gameplay/"
#include <memory>


class EffectManager;

class GameManager {

public:
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

	void setSpawnManager(std::shared_ptr<SpawnManager>& p_spawnManaer){
		spawnManager = p_spawnManaer;
	}

	SceneCode getCurrentScene();

private:
	std::shared_ptr<EventManager> eventManager;
	std::shared_ptr<EffectManager> effectManager;
	std::shared_ptr<SpawnManager> spawnManager;
	SceneCode currentScene;
};