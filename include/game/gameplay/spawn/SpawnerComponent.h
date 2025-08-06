#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/event/Requests.h"






class SpawnerComponent : public Component{

public:

	SpawnerComponent(SpawnRequest req, float spawnTime) : spawnTime(spawnTime){
		addSpawnRequest(req);
		currentLeftTime = spawnTime;
	}

	void addSpawnRequest(SpawnRequest req){
		spawnList.push_back(req);
	}
	
	float spawnTime;
	float currentLeftTime = 1.0f;
	std::vector<SpawnRequest> spawnList;

};