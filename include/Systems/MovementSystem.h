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
                // 단순 이동 로직: x, y를 프레임마다 증가
                transform->x(transform->velocity.x * transform->speed * deltaTime);
                transform->y(transform->velocity.y * transform->speed * deltaTime);
            }else{
                std::cout << "Entity doesn't have TransformComponent. ID: " << entity->getId() << std::endl;
            }
        }
    }


};
