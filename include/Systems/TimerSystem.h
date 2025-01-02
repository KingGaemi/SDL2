#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/StateComponent.h"
#include "Components/LifeTimeComponent.h"
#include "Components/DashComponent.h"




class TimerSystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

		for(auto& entity : entities){

			if(entity->isActive && (entity->hasComponent<LifeTimeComponent>() || entity->hasComponent<StateComponent>()
				|| entity->hasComponent<DashComponent>())){
				auto stateComp = entity->getComponent<StateComponent>();
				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();
				auto dashComp = entity->getComponent<DashComponent>();
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

				if(dashComp){
					if(dashComp->currentTime > 0){
						dashComp->currentTime -= deltaTime;
					}else{
						dashComp->currentTime = 0;
					}
					
					// if(dashComp->keyUpTime > 0){
					// 	dashComp->keyUpTime -= deltaTime;
					// }else{
					// 	dashComp->keyUpTime = 0;
					// }

				}


			}
		}

	}


};