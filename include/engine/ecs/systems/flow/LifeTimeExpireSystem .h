#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/ECSCoordinator.h"
#include "engine/ecs/components/flow/LifeTimeComponent.h"
#include <iostream>


class LifeTimeExpireSystem : public System{


public:
	LifeTimeExpireSystem(ComponentManager* cm,
                         EntityManager* em,
                         const std::vector<EntityID>& ents)
      : System(cm, em, ents) {}
	  
	void update(float deltaTime) override {

		for(auto& entity : entities){
			if(!entity->isActive) continue;
			if(entity->hasComponent<LifeTimeComponent>()){

				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();
				if(lifeTimeComp && lifeTimeComp->lifeTime <= 0) entity->terminate = true;

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