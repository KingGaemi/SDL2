#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"

class EffectSystem : public System{

public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

	void floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime);
};