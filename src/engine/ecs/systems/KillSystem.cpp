#include "Systems/KillSystem.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/HpBarComponent.h"
#include "Groups.h"


void KillSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity : entities){
		if(entity->hasComponent<StatusComponent>()){

			auto statusComp = entity->getComponent<StatusComponent>();
			auto stateComp = entity->getComponent<StateComponent>();

			if(statusComp && !statusComp->isAlive){
				if(stateComp){
					if(stateComp->inMotion) continue;
				}
				
				if(entity->hasComponent<PlayerTag>()){
					auto playerComp = entity->getComponent<PlayerTag>();
					playerComp->life -= 1;
					if(playerComp->life <= 0){
						gameManager->gameOver(1);
						entity->removeComponent<HpBarComponent>();
					}
				}else if(entity->hasComponent<CoreTag>()){
					gameManager->gameOver(2);
				}else if(entity->hasComponent<BossTag>()){
					gameManager->stageClear();
				}else{
					entity->terminate = true;
				}
			}
		}
	}
}