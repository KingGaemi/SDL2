#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {
        for (auto& entity : entities) {

            if(entity->hasComponent<TransformComponent>()){

                auto transform = entity->getComponent<TransformComponent>();
                if (transform) {
                    
                    transform->x(transform->position.x + transform->velocity.x * deltaTime * 100);
                    transform->y(transform->position.y + transform->velocity.y * deltaTime * 100);

                }else{
                    std::cout << "Entity doesn't have TransformComponent. ID: " << entity->getId() << std::endl;
                }
            }
        }
    }


};
