#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Components/AnimationComponent.h"
#include "Components/SpriteComponent.h"


class AnimationSystem : public System {


public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
	void Init();
	json createAnimation(const std::string& name, const std::string& type, bool loop,
                     int startX, int startY, int frameCount, int gap, float duration);
private:

	void updateAnimation(std::shared_ptr<AnimationComponent> animComp, std::shared_ptr<SpriteComponent> spriteComp, float deltaTime);
};






