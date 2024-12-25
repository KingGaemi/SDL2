#pragma once
#include "ECS/Component.h"
#include "Vector2D.h"

struct Direction {
	int hDir; // Horizontal
	int vDir; // Vertical
};

class DirectionComponent : public Component {
public:
    Direction direction;

    DirectionComponent() : direction{0, 0} {}
    DirectionComponent(int dx, int dy) : direction{dx, dy} {}

    void set(int dx, int dy) { direction.hDir = dx; direction.vDir = dy; }
    int hDir() const { return direction.hDir; }
    int vDir() const { return direction.vDir; }

    Vector2D dirToVector() {

        Vector2D dir;

        dir.x = direction.hDir;
        dir.y = direction.vDir;

        return dir;

    }
};
