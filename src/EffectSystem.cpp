# define M_PI           3.14159265358979323846
#include "Systems/EffectSystem.h"
#include "Components/SpriteComponent.h"
#include "Components/FloatingEffectComponent.h"
#include "Components/StatusComponent.h"
#include "Components/HpBarComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ShakeEffectComponent.h"
#include "Components/ItemComponent.h"
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
		if(entity->hasComponent<ShakeEffectComponent>()){
			ShakeEffect(entity, deltaTime);
		}
		if(entity->hasComponent<ItemComponent>()){
			auto itemComp = entity->getComponent<ItemComponent>();
			if(itemComp&&itemComp->onField) itemShadowEffect(entity);			
		}
		if(entity->hasComponent<StatusComponent>()){
			damageTextEffect(entity);
		}
		
	}
	// if(player){
	// 	hpBarControl(player);
	// }

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

	float gap = (hpBarComp->w* hpBarComp->sc / (partitions + 1));
	int drawPartitions = statusComp->currentHp / amount;

	
	EffectRequest req;
	float x = posComp->x - hpBarComp->w/2 * hpBarComp->sc;
	float y = posComp->y - (transComp->height) + offsetY - hpBarComp->h/2 * hpBarComp->sc;
	float w = hpBarComp->w * hpBarComp->sc;
	float h = hpBarComp->h * hpBarComp->sc;
	req.textureId = "all_ui";
	req.dstRect = {x, y, w, h};

	if(!statusComp->isAlive){
		req.srcRect = {871, 70, 34, 5}; //empty frame,gage
		effectManager->pendingEffects.push_back(req);
		return;
	}
	


	//draw frame
	if(percentage== 1.0f){
		req.srcRect = {631, 70, 34, 5}; //frame
	}else{
		req.srcRect = {679, 70, 34, 5};
	}
	effectManager->pendingEffects.push_back(req);


	//draw gage
	if(percentage< 1.0f){
		req.srcRect = {681+static_cast<int>((1-percentage)*100/3.3), 79, 30, 3}; // gage		
		req.dstRect = {x+2* hpBarComp->sc, y+hpBarComp->sc, w-4* hpBarComp->sc, h-2* hpBarComp->sc};
		effectManager->pendingEffects.push_back(req);
	}

	// if(drawPartitions <20){
	// 	req.textureId = "black";
	// 	req.dstRect.w = 1;
	// 	for(int i = 0 ; i < drawPartitions ; i++){
	// 		req.dstRect.x += gap;	
	// 		effectManager->pendingEffects.push_back(req);
	// 	}
	// }
}

void EffectSystem::ShakeEffect(std::shared_ptr<Entity>& entity, float deltaTime){

	auto sprite = entity->getComponent<SpriteComponent>();
	Vector2D dstVec = {sprite->dstRect.x, sprite->dstRect.y};
	auto shakeComp = entity->getComponent<ShakeEffectComponent>();
	
	
	if (shakeComp && shakeComp->shakeTime > 0) {
	    shakeComp->shakeTime -= deltaTime;
	    
	    // 흔들림 강도가 시간이 지나면서 감소
	    float decay = (1.0f - (shakeComp->shakeTime / 1.0f)); // 0 ~ 1의 비율
	    float strength = shakeComp->shakeAmount * (1.0f - decay); // 초기에 크고 빠르게 감소

	    // -2 ~ 2 범위 내에서 랜덤 오프셋 (크기는 strength에 비례)
	    sprite->offsetX = (rand() % 5 - 3) * strength;
	    sprite->offsetY = (rand() % 5 - 3) * strength;
	} else {
	    sprite->offsetX = 0.0f;
	    sprite->offsetY = 0.0f;	    
	}

}


void EffectSystem::itemShadowEffect(std::shared_ptr<Entity>& entity){

	auto posComp = entity->getComponent<PositionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	if(!posComp || !transComp) return;
	if(!entity->isActive) return;

	EffectRequest req;
	float x = posComp->x - transComp->width/2 * transComp->scale;
	float y = posComp->y + transComp->height*2* transComp->scale;
	float w = transComp->width * transComp->scale;
	float h = transComp->height * transComp->scale;
	req.opacity = 0.5f;
	req.textureId = "item_shadow";
	req.zIndex = 0;

	req.srcRect = {0, 0, transComp->width, transComp->height};
	req.dstRect = {x, y, w, h};
	effectManager->pendingEffects.push_back(req);

}

void EffectSystem::damageTextEffect(std::shared_ptr<Entity>& entity){

	auto posComp = entity->getComponent<PositionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto statusComp = entity->getComponent<StatusComponent>();
	if(!posComp || !transComp || !statusComp) return;
	if(!entity->isActive) return;
	if(!statusComp->damagedRecently) return;


	EffectRequest req;
	req.textureId = "damageText";
	req.zIndex = 10;
	req.textNumber = statusComp->recentDamage;
	float w = 25.0f;
	int n = (req.textNumber > 0) ? static_cast<int>(std::log10(req.textNumber)) : 0;
	w += n * 7.0f;
	float h = 40.0f;	
	float x = posComp->x - w/2;
	float y = posComp->y - h*1.2f - transComp->height - (statusComp->recentTime - statusComp->timer)*10;;
	req.dstRect = {x, y, w, h};
	effectManager->pendingEffects.push_back(req);

}