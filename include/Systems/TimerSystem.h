#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "Components/StateComponent.h"
#include "Components/LifeTimeComponent.h"




class TimerSystem : public System {

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

		for(auto& entity : entities){

			auto stateComp = entity->getComponent<StateComponent>();
			auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();

			if(stateComp){
				stateComp->stateTimer -= deltaTime;
			}

			if(lifeTimeComp){
				lifeTimeComp->lifeTime -= deltaTime;
			}
		}

	}


};