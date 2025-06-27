#pragma once
#include "Manager/SpawnManager.h"





void SpawnManager::SpawnWave(const MonsterWave& wave) {
    SpawnRequest req;
    req.entityType = EntityType::Unit;
    req.name = wave.monsterName;

    for(int i = 0 ; i < wave.amount ; ++i){
        ecsManager->pendingSpawns.push_back(req);
    }

}