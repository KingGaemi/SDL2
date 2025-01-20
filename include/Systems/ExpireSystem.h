#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/LifeTimeComponent.h"
#include "Components/StatusComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/StateComponent.h"
#include "Components/ProjectileComponent.h"
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

				if(entity->hasComponent<StateComponent>()){
					auto stateComp = entity->getComponent<StateComponent>();

					if(statusComp && !statusComp->alive && !stateComp->inMotion) entity->terminate = true;
				}else{

					if(statusComp && !statusComp->alive) entity->terminate = true;
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