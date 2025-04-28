#include "Systems/CollisionEventHandlerSystem.h"
#include "Components/StatusComponent.h"
#include "Components/ItemComponent.h"
#include "Groups.h"
#include <iostream>

void CollisionEventHandlerSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	auto& collisionEvents = ecsManager->getCollisionEvents();

	if(!collisionEvents.empty()){
		for(auto& colEvt : collisionEvents){

			auto entityA = colEvt.entityA;
			auto entityB = colEvt.entityB;

			// EntityID A = entityA->getId();
        	// EntityID B = entityB->getId();

			if(!entityA->isActive || !entityB->isActive) continue;

			if(entityA->hasComponent<ItemComponent>() || entityB->hasComponent<ItemComponent>()){				
				applyRoot(entityA, entityB);
				applyRoot(entityB, entityA);
			}
		}
	}
}



void CollisionEventHandlerSystem::applyRoot(std::shared_ptr<Entity> charactor, std::shared_ptr<Entity> item) {
    if (charactor->hasComponent<StatusComponent>() && item->hasComponent<ItemComponent>()
    	&& charactor->hasComponent<TeamTag>()) {
        auto statusComp = charactor->getComponent<StatusComponent>();
    	auto itemComp = item->getComponent<ItemComponent>();
        auto teamComp = charactor->getComponent<TeamTag>();

        if(!statusComp->isAlive) return;

        if(teamComp->teamCode != TeamCode::Ally) return;

	    if (!itemComp->consumed) {
	    	//temp
	    	statusComp->currentHp = statusComp->maxHp;
	    	statusComp->attackSpeed += 0.2f;
	    	statusComp->movementSpeed += 5.0f;
	    	statusComp->physicalDamage += 10.0f;
	    	itemComp->consumed = true;
	    	itemComp->currentStack -= 1;
	    	if(itemComp->currentStack <= 0) item->terminate = true;
	    } 
    }
}
