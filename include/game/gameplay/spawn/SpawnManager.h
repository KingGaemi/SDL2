#pragma once
#include <memory>
#include <ECS/ECSManager.h>
#include "Requests.h"

struct MonsterWave{

	std::string monsterName; // same as prefab
	int waveLevel = 1;
	int amount = 5; // each portal
	float amountMultiple = 1.0f;
	// float strongMultiple

};



class SpawnManager {

public:
    SpawnManager(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {};

    
    void SpawnWave(const MonsterWave& wave);

    
private:
    std::shared_ptr<ECSManager> ecsManager;


};