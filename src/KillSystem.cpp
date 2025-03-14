#include "Systems/KillSystem.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"


void KillSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity : entities){
		if(entity->hasComponent<StatusComponent>()){

			auto statusComp = entity->getComponent<StatusComponent>();
			auto stateComp = entity->getComponent<StateComponent>();

			if(statusComp && !statusComp->isAlive){
				if(stateComp){
					if(stateComp->inMotion) continue;
				}
				entity->terminate = true;
				// if(entity->hasComponent<HpBarComponent>()){
				// 	auto hpBarComp = entity->getComponent<HpBarComponent>();
				// 	hpBarComp->hpGage->terminate = true;
				// 	hpBarComp->hpFrame->terminate = true;
				// }
			}
			
		}
	}

}