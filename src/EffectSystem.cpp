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


		if(entity->hasComponent<PlayerTag>()){
			player = entity;
		}
		// if(entity->hasComponent<HpGageTag>()){
		// 	hpGage = entity;
		// }
		if(entity->hasComponent<StatusComponent>() && entity->hasComponent<HpBarComponent>()){
			hpBarControl(entity);
		}
	}
	if(player){
		hpBarControl(player);
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

	if(!entity->hasComponent<PlayerTag>()&&(statusComp->currentHp == statusComp->maxHp)) return;

	float offsetY = hpBarComp->offsetY;	
	float percentage = statusComp->percentage;
	if(percentage<= 0.03) percentage = 0.03;

	int amount = 100;
	int maxHp = statusComp->maxHp;
	int partitions = maxHp / amount;
	if(maxHp%amount == 0) partitions--;
	// if(partitions >= 30){
	// 	amount *= 10;
	// 	partitions = maxHp / amount;
	// }

	float gap = (hpBarComp->w / (partitions + 1)) * hpBarComp->sc;
	int drawPartitions = statusComp->currentHp / amount;

	// if(statusComp->currentHp == statusComp->maxHp) drawPartitions--;
	EffectRequest req;
	float x = posComp->x - hpBarComp->w/2 * hpBarComp->sc;
	float y = posComp->y - (transComp->height) + offsetY - hpBarComp->h/2 * hpBarComp->sc;
	float w = hpBarComp->w * hpBarComp->sc;
	float h = hpBarComp->h * hpBarComp->sc;
	req.textureId = "hp_bar_frame";

	req.srcRect = {0, 0, hpBarComp->w, hpBarComp->h};
	req.dstRect = {x, y, w, h};
	effectManager->pendingEffects.push_back(req);

	req.textureId = "hp_bar_gage";
	req.dstRect = {x, y, w*percentage, h};
	if(!statusComp->isAlive) {
		req.dstRect = {x, y, 0, h};
		effectManager->pendingEffects.push_back(req);
		return;
	}
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


	// gageSprite->dstRect.w = static_cast<float>(gageSprite->originWidth) * percentage * gageSprite->scale;
	// gageSprite->srcRect.w = static_cast<float>(gageSprite->originWidth) * percentage * gageSprite->scale;
	// gageSprite->offsetX = -(static_cast<float>(gageSprite->originWidth/2) * (1-percentage));
	
	

 
}