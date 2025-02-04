#pragma once
#include "ECS/Component.h"
#include "Vector2D.h"
#include "myMath.h"
#include <map>

struct Direction {
	int hDir; // Horizontal
	int vDir; // Vertical
};

class DirectionComponent : public Component {
public:
    Direction direction;

    DirectionComponent() : direction{0, 1} {}
    DirectionComponent(int dx, int dy) : direction{dx, dy} {}
    DirectionComponent(Direction direction) : direction(direction) {}


    void set(int dx, int dy) { direction.hDir = dx; direction.vDir = dy; }
    void set(Direction p_direction) {direction = p_direction;}
    int hDir() const { return direction.hDir; }
    int vDir() const { return direction.vDir; }

    Vector2D dirToVector() {

        Vector2D dir;

        dir.x = direction.hDir;
        dir.y = direction.vDir;

        return dir;

    }

    float getAngle() {
        static const std::map<std::pair<int, int>, float> directionToAngle = {
            {{ 0, -1},  270.0f},  // 위
            {{ 1, -1},  315.0f},  // 오른쪽 위
            {{ 1,  0},   0.0f},  // 오른쪽
            {{ 1,  1}, 45.0f},  // 오른쪽 아래
            {{ 0,  1}, 90.0f},  // 아래
            {{-1,  1}, 135.0f},  // 왼쪽 아래
            {{-1,  0}, 180.0f},  // 왼쪽
            {{-1, -1}, 225.0f},  // 왼쪽 위
            {{ 0,  0},   0.0f}   // 정지 (기본값)
        };


        auto it = directionToAngle.find({direction.hDir, direction.vDir});
        if (it != directionToAngle.end()) {
            return it->second;
        }
        return 0.0f; // 기본값
    }

    float getRadian() {
        static const std::map<std::pair<int, int>, float> directionToAngle = {
            {{ 0, -1},  270.0f},  // 위
            {{ 1, -1},  315.0f},  // 오른쪽 위
            {{ 1,  0},   0.0f},  // 오른쪽
            {{ 1,  1}, 45.0f},  // 오른쪽 아래
            {{ 0,  1}, 90.0f},  // 아래
            {{-1,  1}, 135.0f},  // 왼쪽 아래
            {{-1,  0}, 180.0f},  // 왼쪽
            {{-1, -1}, 225.0f},  // 왼쪽 위
            {{ 0,  0},   0.0f}   // 정지 (기본값)
        };


        auto it = directionToAngle.find({direction.hDir, direction.vDir});
        if (it != directionToAngle.end()) {
            return it->second * (M_PI / 180.0f);
        }
        return 0.0f; // 기본값
    }
};
