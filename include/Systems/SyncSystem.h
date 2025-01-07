#pragma once

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformComponent.h"




class SyncSystem : public System {


public:
	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

		for(auto& entity : entities){
			if(!entity->isActive) return;
			if(entity->hasComponent<SpriteComponent>() && entity->hasComponent<TransformComponent>()){

				auto spriteComp = entity->getComponent<SpriteComponent>();
				auto transComp = entity->getComponent<TransformComponent>();

				if(spriteComp&&transComp){
					spriteComp->dstRect.w = (int)(transComp->width * transComp->scale);
					spriteComp->dstRect.h = (int)(transComp->height * transComp->scale);
				}

			} 


		}


	}
};






