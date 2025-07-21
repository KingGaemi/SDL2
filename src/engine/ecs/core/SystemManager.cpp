#pragma once
#include "engine/ecs/core/SystemManager.h"


void SystemManager::update(float deltaTime) {

        // if(mapEntity) mapEntity->isActive = activeMap; // temp

        std::sort(registered.begin(), registered.end(),
            [](const SystemRegistration& a, const SystemRegistration& b) {
                return a.priority < b.priority;
            }
        );

        for (auto& reg : registered) {
            if (reg.group == SystemGroup::Logic) {
                reg.system->update(deltaTime);
            }
        }

        for (auto& reg : registered) {
            if (reg.group == SystemGroup::Event) {
                reg.system->update(deltaTime);
            }
        }
}




void SystemManager::updateLogic(float dt){
    for (auto& reg : registered) {
        if (reg.group == SystemGroup::Logic) {
            reg.system->update(entities, deltaTime);
        }
    }
}