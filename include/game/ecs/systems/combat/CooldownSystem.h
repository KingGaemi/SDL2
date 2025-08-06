#pragma once
#include "engine/ecs/core/System.h"
#include "engine/ecs/core/ECSCoordinator.h"
#include "game/ecs/components/combat/CooldownComponent.h"





class CooldownSystem : public System{


public:


	// CooldownSystem(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}

	void update(float deltaTime) override {

		for(auto& entity : entities){

			if(entity->isActive && entity->hasComponent<CooldownComponent>()){

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