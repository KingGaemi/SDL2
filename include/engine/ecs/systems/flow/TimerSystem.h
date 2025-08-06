#pragma once

#include "engine/ecs/core/System.h"
#include "game/ecs/components/status/StateComponent.h"
#include "engine/ecs/components/flow/LifeTimeComponent.h"
#include "game/ecs/components/movement/DashComponent.h"
#include "game/ecs/components/combat/ProjectileComponent.h"
#include "game/ecs/components/status/StatusComponent.h"
#include <iostream>



class TimerSystem : public System {

public:

	void update(float deltaTime){

		for(auto& entity : entities){

			if(entity->isActive && (entity->hasComponent<LifeTimeComponent>() ||
				entity->hasComponent<StateComponent>() ||
				entity->hasComponent<DashComponent>()  ||
				entity->hasComponent<DashComponent>() ||
				entity->hasComponent<ProjectileComponent>() ||
				entity->hasComponent<StatusComponent>() )){
				auto stateComp = entity->getComponent<StateComponent>();
				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();
				auto dashComp = entity->getComponent<DashComponent>();
				auto projectileComp = entity->getComponent<ProjectileComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
			
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

				if(statusComp){
					if(statusComp->timer > 0 ) statusComp->timer -= deltaTime;
					else {
						statusComp->damagedRecently = false;
						statusComp->recentDamage = 0;
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