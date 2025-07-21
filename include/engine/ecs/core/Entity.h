#pragma once
#include "Component.h"
#include "engine/ecs/core/Types.h"
#include <stdexcept>
#include <iostream>

using namespace ecs;
class Entity {
public:
    Entity(EntityID id) : id(id) {}
    EntityID getId() const { return id; }
    bool isActive = true;
    bool terminate = false;
    bool isVisible = true;
private:
    EntityID id;
};
