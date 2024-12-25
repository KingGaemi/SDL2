#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"

class PositionComponent : public Component {
public:
    Vector2D position;

    PositionComponent() { position.x = 0.0f; position.y = 0.0f;}
    PositionComponent(float x, float y) : position(x, y) {}
    PositionComponent(const Vector2D& pos) : position(pos) {}

    float x() const { return position.x; }
    float y() const { return position.y; }


    void set(float xVal, float yVal) { position.x = xVal; position.y = yVal; }
    void set(const Vector2D& pos) { position = pos; }
    void add(float xVal, float yVal) { position.x += xVal; position.y += yVal; }
    void add(const Vector2D& pos) { position += pos; }
};
