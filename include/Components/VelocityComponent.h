#pragma once
#include "ECS/Component.h"
#include "Vector2D.h"

class VelocityComponent : public Component {
public:

    Vector2D velocity; // 이동 속도

    VelocityComponent() : velocity(0.0f, 0.0f) {}
    VelocityComponent(float vx, float vy) : velocity(vx, vy) {}
    VelocityComponent(const Vector2D& vel) : velocity(vel) {}

    void set(float vx, float vy) { velocity.x = vx; velocity.y = vy; }
    void set(const Vector2D& vel) { velocity = vel; }
    void add(float vx, float vy) { velocity.x += vx; velocity.y += vy; }
    void add(const Vector2D& vel) { velocity += vel;}

    float x() { return velocity.x; }
    float y() { return velocity.y; }

    void zero() { velocity.x = 0.0f;  velocity.y = 0.0f;}

    Vector2D velo() { return velocity; }
};
