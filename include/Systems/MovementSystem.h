#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/ColliderComponent.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {
        for (auto& entity : entities) {

            if(entity->isActive && entity->hasComponent<VelocityComponent>()){

                auto posComp = entity->getComponent<PositionComponent>();
                auto veloComp = entity->getComponent<VelocityComponent>();
                if (!posComp || !veloComp) continue;
                    
                posComp->add(veloComp->velo() * deltaTime);
                        
                // if(entity->hasComponent<ColliderComponent>()){
                //     auto colliderComp = entity->getComponent<ColliderComponent>();
                //     if(!colliderComp) continue;

                //     colliderComp->add(veloComp->velo() * deltaTime);
                // }


            }
        }
    }
};
