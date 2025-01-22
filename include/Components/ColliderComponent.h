#pragma once
#include "ECS/Component.h"
#include "Rect.h"
#include "Vector2D.h"
#include <string>
#include <cmath>


enum class ColliderType{
	Unit,
	Object,
	Projectile,
	Portal,
	Wall,
	Beacon
};

struct CircleCollider {
    float offsetX;  // 엔티티 중심(혹은 position)에서의 오프셋 X
    float offsetY;  // 오프셋 Y
    float radius;   // 원의 반지름

    // 월드 좌표계에서 계산된 실제 중심
};

class ColliderComponent : public Component{

public:
	Rect collider;
	CircleCollider circleCollider;
	ColliderType colliderType;
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	float rotation = 0.0f;

	ColliderComponent() {}
	// ColliderComponent(Vector2D position, std::string tag) : position(position), tag(tag) {
	// 	collider.x = static_cast<int>(std::round(position.x));
	// 	collider.y = static_cast<int>(std::round(position.y));
	// }
	ColliderComponent(int w, int h, float sc, ColliderType colliderType) : colliderType(colliderType){
		collider.x = 0;
		collider.y = 0;
		collider.w = w * sc;
		collider.h = h * sc;
	}
	ColliderComponent(int w, int h, float sc, float offX, float offY, ColliderType colliderType) : colliderType(colliderType){
		collider.x = 0;
		collider.y = 0;
		collider.w = w * sc;
		collider.h = h * sc;
		offsetX = offX;
		offsetY = offY;
	}
	ColliderComponent(float radius, float offX, float offY, ColliderType colliderType) : colliderType(colliderType){
		collider.x = 0;
		collider.y = 0;
		circleCollider.radius = radius;
		circleCollider.offsetX = offX;
		circleCollider.offsetY = offY;
	}
};
