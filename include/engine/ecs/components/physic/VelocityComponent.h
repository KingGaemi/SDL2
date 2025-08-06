#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/math/Vector2D.h"
#include <math.h>

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

    float length(){
        return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    }
    Vector2D velo() { return velocity; }

};
