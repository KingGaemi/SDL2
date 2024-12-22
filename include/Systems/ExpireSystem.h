#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/LifeTimeComponent.h"





class ExpireSystem : public System{


public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

		for(auto& entity : entities){

			if(entity->hasComponent<LifeTimeComponent>()){

				auto lifeTimeComp = entity->getComponent<LifeTimeComponent>();

				if(lifeTimeComp && lifeTimeComp->lifeTime < 0) entity->isActive = false;
			}

		}

	}

private:


};