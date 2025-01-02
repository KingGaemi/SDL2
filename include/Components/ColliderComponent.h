#pragma once
#include "ECS/Component.h"
#include "Rect.h"
#include "Vector2D.h"
#include <string>
#include <cmath>


class ColliderComponent : public Component{

public:

	Rect collider;
	std::string tag;
	float offsetX = 0.0f;
	float offsetY = 0.0f;



	ColliderComponent() {}
	// ColliderComponent(Vector2D position, std::string tag) : position(position), tag(tag) {
	// 	collider.x = static_cast<int>(std::round(position.x));
	// 	collider.y = static_cast<int>(std::round(position.y));
	// }
	ColliderComponent(int w, int h, std::string tag) : tag(tag){
		collider.x = 0;
		collider.y = 0;
		collider.w = w;
		collider.h = h;
	}
	ColliderComponent(int w, int h, float offX, float offY, std::string tag) : tag(tag){
		collider.x = 0;
		collider.y = 0;
		collider.w = w;
		collider.h = h;
		offsetX = offX;
		offsetY = offY;
	}


	// void add(const Vector2D& pos) {	position += pos; }



private:




};
