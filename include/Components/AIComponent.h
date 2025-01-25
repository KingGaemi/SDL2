#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "Vector2D.h"

class AIComponent : public Component {
public:
	std::shared_ptr<Entity> target;
	Vector2D targetPos;
};