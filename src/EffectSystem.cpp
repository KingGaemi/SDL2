# define M_PI           3.14159265358979323846
#include "Systems/EffectSystem.h"
#include "Components/SpriteComponent.h"
#include "Components/FloatingEffectComponent.h"
#include "Components/StatusComponent.h"
#include "Components/HpBarComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Renderer.h"
#include "Groups.h"
#include <math.h>
#include <iostream>



void EffectSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity: entities){

		if(entity->hasComponent<FloatingEffectComponent>()){
			floatingEffect(entity, deltaTime);
		}


		// if(entity->hasComponent<PlayerTag>()){
		// 	player = entity;
		// }
		// if(entity->hasComponent<HpGageTag>()){
		// 	hpGage = entity;
		// }
		if(entity->hasComponent<StatusComponent>() && entity->hasComponent<HpBarComponent>()){
			hpBarControl(entity);
		}
	}

}



void EffectSystem::floatingEffect(std::shared_ptr<Entity>& entity, float deltaTime){

	auto floatComp = entity->getComponent<FloatingEffectComponent>();
	floatComp->timeElapsed += deltaTime;
	floatComp->timeElapsed = fmod(floatComp->timeElapsed, 2 * M_PI);
    floatComp->renderOffsetY = floatComp->amplitude 
                            * sin(floatComp->speed 
                            * floatComp->timeElapsed
                            + floatComp->phaseOffset);


       
}


// void EffectSystem::hpBarControl(std::shared_ptr<Entity>& hpGage, std::shared_ptr<Entity>& entity){

// 	auto statusComp = entity->getComponent<StatusComponent>();
// 	auto hpSprite = hpGage->getComponent<SpriteComponent>();

// 	if(!statusComp || !hpSprite) return;
// 	if(!statusComp->isAlive){
// 		hpSprite->dstRect.w = 0;
// 		return;
// 	}

// 	int maxHp = statusComp->maxHp;
// 	int currentHp = statusComp->currentHp;
// 	float percent = static_cast<float>(currentHp) / static_cast<float>(maxHp);

	
// 	hpSprite->dstRect.w = static_cast<float>(hpSprite->originWidth) * percent;
// 	hpSprite->srcRect.w = static_cast<float>(hpSprite->originWidth) * percent;
// 	hpSprite->offsetX = -(static_cast<float>(hpSprite->originWidth/2) * (1-percent)) ;
	
// 	// std::cout <<"reduced" << std::endl;

 
// }


void EffectSystem::hpBarControl(std::shared_ptr<Entity>& entity){

	auto statusComp = entity->getComponent<StatusComponent>();
	auto hpBarComp = entity->getComponent<HpBarComponent>();
	auto posComp = entity->getComponent<PositionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	if(!statusComp || !hpBarComp || !posComp || !transComp) return;
	

	float percentage = statusComp->percentage;
	float offsetY = hpBarComp->offsetY;
	if(percentage<= 0.03) percentage = 0.03;
	auto hpGage = hpBarComp->hpGage;
	auto hpFrame = hpBarComp->hpFrame;

	auto gagePos = hpGage->getComponent<PositionComponent>();
	auto hpGageTrans = hpGage->getComponent<TransformComponent>();
	auto gageSprite = hpGage->getComponent<SpriteComponent>();

	auto framePos = hpFrame->getComponent<PositionComponent>();
	auto frameTrans = hpFrame->getComponent<TransformComponent>();

	gagePos->set(posComp->getVector());
	framePos->set(posComp->getVector());

	gagePos->add(0, -(transComp->height + offsetY));
	framePos->add(0, -(transComp->height + offsetY));

	int amount = 100;
	int maxHp = statusComp->maxHp;
	int partitions = maxHp / amount;
	if(partitions >= 30){
		amount *= 10;
		partitions = maxHp / amount;
	}
	auto gap = (frameTrans->width / partitions + 1)* frameTrans->scale;
	int drawPartitions = statusComp->currentHp / amount;
	if(statusComp->currentHp == statusComp->maxHp) drawPartitions--;
	EffectRequest req;
	req.x = framePos->x - frameTrans->width/2 * frameTrans->scale;
	req.y = framePos->y - frameTrans->height/2 * frameTrans->scale;
	req.h = frameTrans->height * frameTrans->scale;
	req.w = 1;
	req.textureId = "hp_bar_gage";

	req.srcRect = {0, 0, hpGageTrans->width * hpGageTrans->scale , hpGageTrans->height * hpGageTrans->scale};
	float offsetX = -(static_cast<float>(frameTrans->width/2) * (1-percentage)) * gageSprite->scale;
	req.dstRect = {req.x + offsetX, req.y, static_cast<float>(frameTrans->width) * percentage * hpGageTrans->scale, req.h};
	effectManager->pendingEffects.push_back(req);


	req.textureId = "black";
	req.dstRect.w = 1;
	for(int i = 0 ; i < drawPartitions ; i++){
		req.dstRect.x += gap;	
		effectManager->pendingEffects.push_back(req);
	}
	

	// // gageSprite->dstRect.w = static_cast<float>(frameTrans->width) * percentage* gageSprite->scale;
	// hpGageTrans->width = static_cast<float>(frameTrans->width) * percentage ;
	// // gageSprite->srcRect.h = frameTrans->width * gageSprite->scale;
	// gageSprite->srcRect.w = frameTrans->width * percentage;
	// gageSprite->offsetX = -(static_cast<float>(frameTrans->width/2) * (1-percentage)) * gageSprite->scale;


	if(!statusComp->isAlive){
		gageSprite->dstRect.w = 0;
		hpGageTrans->width = 0;
	}

	// gageSprite->dstRect.w = static_cast<float>(gageSprite->originWidth) * percentage * gageSprite->scale;
	// gageSprite->srcRect.w = static_cast<float>(gageSprite->originWidth) * percentage * gageSprite->scale;
	// gageSprite->offsetX = -(static_cast<float>(gageSprite->originWidth/2) * (1-percentage));
	
	

 
}