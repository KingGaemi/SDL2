#pragma once

#include "ecs/System.h"
#include "ecs/Entity.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
};
