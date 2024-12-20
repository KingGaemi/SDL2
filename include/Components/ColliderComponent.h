#pragma once
#include "ECS/Component.h"
#include "Rect.h"
#include "Vector2D.h"
#include <string>
#include <cmath>


class ColliderComponent : public Component{

public:

	Vector2D position;
	std::string tag;
	Rect collider;



	ColliderComponent() {}
	ColliderComponent(Vector2D position, std::string tag) : position(position), tag(tag) {
		collider.x = static_cast<int>(std::round(position.x));
		collider.y = static_cast<int>(std::round(position.y));
	}
	ColliderComponent(Vector2D position, std::string tag, int w, int h) : position(position), tag(tag){
		collider.x = static_cast<int>(std::round(position.x));
		collider.y = static_cast<int>(std::round(position.y));
		collider.w = w;
		collider.h = h;
	}



private:




};
