#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include <iostream>

class MovementSystem : public System {
public:
    void update(float deltaTime) override;
};
