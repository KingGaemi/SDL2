#pragma once

#include "engine/ecs/core/Entity.h"
#include "engine/ecs/core/System.h"
#include "engine/ecs/components/rendering/SpriteComponent.h"
#include "game/ecs/components/animation/AnimationComponent.h"


class AnimationSystem : public System {


public:
	void update(float deltaTime) override;

private:

	void updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime);
};






