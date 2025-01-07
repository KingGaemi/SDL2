#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"

class PositionComponent : public Component {
public:
    int x, y;

    PositionComponent() { x = 0.0f; y = 0.0f;}
    PositionComponent(float x, float y) : x(x), y(y) {}
    PositionComponent(const Vector2D& pos) : x(pos.x) , y(pos.y) {}

    
    void set(int xVal, int yVal) { x = xVal; y = yVal; }
    void set(const Vector2D& pos) { x = pos.x; y = pos.y; }
    void add(int xVal, int yVal) { x += xVal; y += yVal; }
    void add(const Vector2D& pos) { x += pos.x; y += pos.y;}
};
