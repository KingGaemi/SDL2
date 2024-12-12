#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"

class PositionComponent : public Component {
public:
    float x, y;
    PositionComponent() : { x = 0f; y = 0f;}
    PositionComponent(float x, float y) : x(x), y(y) {}
};
