#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/StateComponent.h"
#include "Components/LifeTimeComponent.h"
#include "Components/DashComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ExplosionComponent.h"
#include <iostream>



class TimerSystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

		for(auto& entity : entities){

			if(entity->isActive && (entity->hasComponent<LifeTimeComponent>() ||
				entity->hasComponent<StateComponent>() ||
				entity->hasComponent<DashComponent>()  ||
				entity->hasComponent<DashComponent>() ||
				entity->hasComponent<ProjectileComponent>() ||
				entity->hasComponent<StatusComponent>() ||
				entity->hasComponent<ExplosionComponent>())){
				auto stateComp = entity->getComponent<StateComponent>();
				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();
				auto dashComp = entity->getComponent<DashComponent>();
				auto projectileComp = entity->getComponent<ProjectileComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto explosionComponent = entity->getComponent<ExplosionComponent>();
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

				if(explosionComponent){
					if(explosionComponent->currentTime > 0) explosionComponent->currentTime -= deltaTime;
					if(explosionComponent->currentTime <= 0) {
						explosionComponent->currentTime = 0;
						if(!explosionComponent->readyToExplode) explosionComponent->readyToExplode = true;
					}
				}

			}
		}

	}


};