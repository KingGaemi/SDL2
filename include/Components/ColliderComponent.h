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



class ColliderComponent : public Component{

public:
	Rect collider;
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
};
