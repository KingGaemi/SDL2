#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Components/AnimationComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"


class AnimationSystem : public System {


public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;


private:

	void updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime);
};






