#include "ECS/EntityFactory.h"
#include "ECS/ECSManager.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include <iostream>


std::shared_ptr<Entity> EntityFactory::createBackgroundEntity(std::shared_ptr<ECSManager> ecsManager, const std::string& textureName){

	auto entity = ecsManager->createEntity();
	entity->addComponent<TransformComponent>();
	entity->addComponent<SpriteComponent>(textureName, 1280, 800);

	return entity;
}



std::shared_ptr<Entity> EntityFactory::createPlayerEntity(std::shared_ptr<ECSManager> ecsManager){

	auto player = ecsManager->createEntity();
	player->addComponent<TransformComponent>();
	player->addComponent<SpriteComponent>("player_sprite", 21, 28, 3);
	player->addComponent<AnimationComponent>();
	auto animComp = player->getComponent<AnimationComponent>();
	player->addComponent<PlayableComponent>();


	int currentPoint;
	int nextPoint;

	AnimationData d_idleAnim;

	d_idleAnim.name = "d_idle";
	nextPoint = addAnimationFrames(d_idleAnim, 13, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	d_idleAnim.loop = true;
	animComp->animations["d_idle"] = d_idleAnim;
	animComp->playAnimation("d_idle");


	AnimationData d_specialAnim;
	d_specialAnim.name = "d_special";
	nextPoint = addAnimationFrames(d_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	d_specialAnim.loop = true;
	animComp->animations["d_special"] = d_specialAnim;


	AnimationData d_walkAnim;
	d_walkAnim.name = "d_walk";
	nextPoint = addAnimationFrames(d_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	d_walkAnim.loop = true;
	animComp->animations["d_walk"] = d_walkAnim;


	AnimationData s_idleAnim;
	s_idleAnim.name = "s_idle";
	nextPoint = addAnimationFrames(s_idleAnim, currentPoint, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	s_idleAnim.loop = true;
	animComp->animations["s_idle"] = s_idleAnim;


	AnimationData s_specialAnim;
	s_specialAnim.name = "s_special";
	nextPoint = addAnimationFrames(s_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	s_specialAnim.loop = true;
	animComp->animations["s_special"] = s_specialAnim;


	AnimationData s_walkAnim;
	s_walkAnim.name = "s_walk";
	nextPoint = addAnimationFrames(s_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	s_walkAnim.loop = true;
	animComp->animations["s_walk"] = s_walkAnim;



	AnimationData u_walkAnim;
	u_walkAnim.name = "u_walk";
	nextPoint = addAnimationFrames(u_walkAnim, currentPoint, 4, 21, 28, 0.2f, 48, 4);
	currentPoint = nextPoint;
	u_walkAnim.loop = true;
	animComp->animations["u_walk"] = u_walkAnim;


	AnimationData u_specialAnim;
	u_specialAnim.name = "u_special";
	nextPoint = addAnimationFrames(u_specialAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	u_specialAnim.loop = true;
	animComp->animations["u_special"] = u_specialAnim;


	AnimationData u_idleAnim;
	u_idleAnim.name = "u_idle";
	nextPoint = addAnimationFrames(u_idleAnim, currentPoint, 4, 21, 28, 0.2f, 48, 6);
	currentPoint = nextPoint;
	u_idleAnim.loop = true;
	animComp->animations["u_idle"] = u_idleAnim;






	return player;	

}
    // ... 필요한 팩토리 메서드를 추가





int EntityFactory::addAnimationFrames(AnimationData& animData, int x, int y, int w, int h, float duration, int interval, int count){

	int desX = x;
	int desY = y;

	for (int i = 0; i < count; ++i)
	{
		desX = x + (interval * i);
		animData.frames.push_back({desX, desY, w, h, duration});
	}

	return x + (interval * count);
}