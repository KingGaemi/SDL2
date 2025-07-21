#pragma once

#include "engine/ecs/core/Component.h"

#include "engine/math/Vector2D.h"

class PositionComponent : public Component {
public:
    float x, y;

    PositionComponent() { x = 0.0f; y = 0.0f;}
    PositionComponent(float x, float y) : x(x), y(y) {}
    PositionComponent(const Vector2D& pos) : x(pos.x) , y(pos.y) {}

    
    Vector2D getVector(){
        Vector2D vector = {x, y};
        return vector;
    }
    void set(float xVal, float yVal) { x = xVal; y = yVal; }
    void set(const Vector2D& pos) { x = pos.x; y = pos.y; }
    void add(float xVal, float yVal) { x += xVal; y += yVal; }
    void add(const Vector2D& pos) { x += pos.x; y += pos.y;}
};
