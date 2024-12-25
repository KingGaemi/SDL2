#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {
        for (auto& entity : entities) {

            if(entity->hasComponent<VelocityComponent>()){

                auto posComp = entity->getComponent<PositionComponent>();
                auto veloComp = entity->getComponent<VelocityComponent>();

                if (posComp && veloComp) {
                
                    posComp->add(veloComp->velo() * deltaTime);
                    
                }else{
                    std::cout << "Entity doesn't have TransformComponent. ID: " << entity->getId() << std::endl;
                }
            }
        }
    }
};
