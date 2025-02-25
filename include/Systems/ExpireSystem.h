#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/LifeTimeComponent.h"
#include "Components/StatusComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/StateComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/HpBarComponent.h"
#include <iostream>




class ExpireSystem : public System{


public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

		for(auto& entity : entities){
			if(!entity->isActive) continue;
			if(entity->hasComponent<LifeTimeComponent>()){

				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();

				if(lifeTimeComp && lifeTimeComp->lifeTime <= 0) entity->terminate = true;

			}

			if(entity->hasComponent<StatusComponent>()){

				auto statusComp = entity->getComponent<StatusComponent>();
				auto stateComp = entity->getComponent<StateComponent>();

				if(statusComp && !statusComp->isAlive){
					if(stateComp){
						if(stateComp->inMotion) continue;
					}
					entity->terminate = true;
					if(entity->hasComponent<HpBarComponent>()){
						auto hpBarComp = entity->getComponent<HpBarComponent>();
						hpBarComp->hpGage->terminate = true;
						hpBarComp->hpFrame->terminate = true;
					}
				}
				
			}

			if(entity->hasComponent<ProjectileComponent>()){

				auto projectileComp = entity->getComponent<ProjectileComponent>();
				
				if(projectileComp && projectileComp->duration <= 0){
					entity->terminate = true;
				}
			}
		}
	}

private:


};