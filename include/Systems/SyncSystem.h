#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ItemComponent.h"
#include "Components/ProjectileComponent.h"
#include <iostream>




class SyncSystem : public System {


public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

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


		}


	}
};






