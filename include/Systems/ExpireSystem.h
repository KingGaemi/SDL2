#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/LifeTimeComponent.h"
#include "Components/StatusComponent.h"





class ExpireSystem : public System{


public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

		for(auto& entity : entities){
			if(!entity->isActive) continue;
			if(entity->hasComponent<LifeTimeComponent>()){

				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();

				if(lifeTimeComp && lifeTimeComp->lifeTime < 0) entity->terminate = true;

			}

			if(entity->hasComponent<StatusComponent>()){

				auto statusComp = entity->getComponent<StatusComponent>();

				if(statusComp && !statusComp->alive) entity->terminate = true;
				
			}

		}

	}

private:


};