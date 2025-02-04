#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "Vector2D.h"


enum class AIType{
	HomingMissile,
	Roaming,
	FindEnemy,
	None
};


class AIComponent : public Component {
public:
	AIComponent(AIType aiType) : aiType(aiType) {}
	std::shared_ptr<Entity> target;
	Vector2D targetPos;
	AIType aiType;
	float updateInterval = 0.1f;
	float timeAccumulator = 0.0f;
};