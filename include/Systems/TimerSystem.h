#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/StateComponent.h"
#include "Components/LifeTimeComponent.h"
#include "Components/DashComponent.h"
#include "Components/ProjectileComponent.h"
#include <iostream>



class TimerSystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

		for(auto& entity : entities){

			if(entity->isActive && (entity->hasComponent<LifeTimeComponent>() ||
				entity->hasComponent<StateComponent>() ||
				entity->hasComponent<DashComponent>()  ||
				entity->hasComponent<DashComponent>() ||
				entity->hasComponent<ProjectileComponent>())){
				auto stateComp = entity->getComponent<StateComponent>();
				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();
				auto dashComp = entity->getComponent<DashComponent>();
				auto projectileComp = entity->getComponent<ProjectileComponent>();
				if(stateComp){
					if(stateComp->stateTimer > 0) stateComp->stateTimer -= deltaTime;
					else{
						stateComp->stateTimer = 0;
						stateComp->inMotion = false;
					}					
				}

				if(lifeTimeComp){
					if(lifeTimeComp->lifeTime > 0) lifeTimeComp->lifeTime -= deltaTime;
					if(lifeTimeComp->lifeTime <= 0) {
						lifeTimeComp->lifeTime = 0;
					}
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

				if(projectileComp){
					if(projectileComp->duration > 0) projectileComp->duration -= deltaTime;
					if(projectileComp->duration <= 0) {
						projectileComp->duration = 0;
					}
				}

			}
		}

	}


};