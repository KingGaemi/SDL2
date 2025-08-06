#pragma once

#include "engine/ecs/core/Entity.h"
#include "engine/ecs/core/System.h"
#include "engine/ecs/core/ECSCoordinator.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ColliderComponent.h"
#include "game/ecs/components/animation/AnimationComponent.h"
#include "game/ecs/components/status/StatusComponent.h"
#include "Components/ItemComponent.h"
#include "game/ecs/components/combat/ProjectileComponent.h"
#include <iostream>




class SyncSystem : public System {


public:
	void update(float deltaTime) override {

		for(auto& entity : entities){
			if(!entity->isActive) return;
			if(entity->hasComponent<TransformComponent>() &&
			(entity->hasComponent<SpriteComponent>() || entity->hasComponent<ColliderComponent>())
			){
				auto spriteComp = entity->getComponent<SpriteComponent>();
				auto transComp = entity->getComponent<TransformComponent>();
				// auto colliderComp = entity->getComponent<ColliderComponent>();

				if(spriteComp&&transComp){
					// std::cout << (int)(transComp->width * transComp->scale) << std::endl;
					if(entity->hasComponent<ItemComponent>()) continue;
					spriteComp->dstRect.w = (int)(transComp->width * transComp->scale);
					spriteComp->dstRect.h = (int)(transComp->height * transComp->scale);
				}

				// if(colliderComp&&transComp){
				// 	// std::cout << (int)(transComp->width * transComp->scale) << std::endl;
				// 	colliderComp->rotation = transComp->rotation;
				// }

			} 

			if(entity->hasComponent<AnimationComponent>() &&
				(entity->hasComponent<StatusComponent>() || entity->hasComponent<ProjectileComponent>())){

				auto animComp = entity->getComponent<AnimationComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto projectileComp = entity->getComponent<ProjectileComponent>();
				if(animComp&&statusComp){
					
					animComp->attackFast = statusComp->attackSpeed;
					animComp->moveFast = statusComp->movementSpeed / 100.0f;
					
				}
				if(animComp&&projectileComp){

					animComp->moveFast = projectileComp->projectileSpeed/ 100.0f;
				}


			}

			if(entity->hasComponent<StatusComponent>()){
				auto statusComp = entity->getComponent<StatusComponent>();
				if(statusComp&&statusComp->isAlive){
					int currentHp = statusComp->currentHp;
					int maxHp = statusComp->maxHp;

					statusComp->percentage = static_cast<float>(currentHp) / static_cast<float>(maxHp);
				}
			}


		}


	}
};






