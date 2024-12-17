#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {
        for (auto& entity : entities) {
            auto transform = entity->getComponent<TransformComponent>();
            if (transform) {
                transform->x(transform->position.x + (transform->direction.x * transform->speed + transform->velocity.x) * deltaTime * 100);
                transform->y(transform->position.y + (transform->direction.y * transform->speed + transform->velocity.y) * deltaTime * 100);
            }else{
                std::cout << "Entity doesn't have TransformComponent. ID: " << entity->getId() << std::endl;
            }
        }
    }


};
