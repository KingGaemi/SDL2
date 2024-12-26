#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/StateComponent.h"
#include "Components/LifeTimeComponent.h"




class TimerSystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

		for(auto& entity : entities){

			if(entity->hasComponent<LifeTimeComponent>() || entity->hasComponent<StateComponent>()){
				auto stateComp = entity->getComponent<StateComponent>();
				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();

				if(stateComp){
					if(stateComp->stateTimer > 0) stateComp->stateTimer -= deltaTime;
					if(stateComp->stateTimer <= 0) {
						stateComp->stateTimer = 0;
						if(stateComp->inMotion) stateComp->inMotion = false;
					}
					
				}

				if(lifeTimeComp){
					lifeTimeComp->lifeTime -= deltaTime;
				}
			}
		}

	}


};