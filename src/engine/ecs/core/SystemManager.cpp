#pragma once
#include "engine/ecs/core/SystemManager.h"


void SystemManager::update(float dt) {

        // if(mapEntity) mapEntity->isActive = activeMap; // temp

        for (auto grp : {SystemGroup::Event,
                         SystemGroup::Logic,
                         SystemGroup::Render,
                         SystemGroup::UI   }) {
            auto& vec = systemsByGroup[size_t(grp)];
            for (auto& reg : vec) {
                reg.system->update(dt);
            }
        }

        // std::sort(registered.begin(), registered.end(),
        //     [](const SystemRegistration& a, const SystemRegistration& b) {
        //         return a.priority < b.priority;
        //     }
        // );

        // for (auto& reg : registered) {
        //     if (reg.group == SystemGroup::Logic) {
        //         reg.system->update(deltaTime);
        //     }
        // }

        // for (auto& reg : registered) {
        //     if (reg.group == SystemGroup::Event) {
        //         reg.system->update(deltaTime);
        //     }
        // }
}




void SystemManager::updateLogic(float dt){
    for (auto& reg : systemsByGroup[size_t(SystemGroup::Logic)])
            reg.system->update(dt);
}