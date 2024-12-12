#pragma once

#include "ECS/Component.h"

class HealthComponent : public Component {
public:
    int health;
    HealthComponent(int h) : health(h) {}
};
