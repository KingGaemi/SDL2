#pragma once

#include "ecs/Entity.h"
#include "ecs/System.h"
#include "Components/AnimationComponent.h"
#include "Components/SpriteComponent.h"


class AnimationSystem : public System {


public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;

private:

	void updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime);
};






