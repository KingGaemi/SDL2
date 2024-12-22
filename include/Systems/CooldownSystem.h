#pragma once

#include "ECS/System.h"
#include "ECS/ECSManager.h"
#include "Components/CooldownComponent.h"





class CooldownSystem : public System{


public:


	// CooldownSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override {

		for(auto& entity : entities){

			if(entity->hasComponent<CooldownComponent>()){

				auto cooldownComp = entity->getComponent<CooldownComponent>();

				if(cooldownComp){

					cooldownComp->updateAllCooldowns(deltaTime);
				}
				
			}

		}

	}

private:

	// std::shared_ptr<ECSManager> ecsManager;

};