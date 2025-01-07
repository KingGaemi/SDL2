#include "Systems/DamageSystem.h"
#include "Components/DamageComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Groups.h"
#include <iostream>




void DamageSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	auto& collisionEvents = ecsManager->getCollisionEvents();

	if(!collisionEvents.empty()){
		for(auto& colEvt : collisionEvents){

			auto entityA = colEvt.entityA;
			auto entityB = colEvt.entityB;

			EntityID A = entityA->getID();
        	EntityID B = entityB->getID();

			if(!entityA->isActive || !entityB->isActive) continue;

        	if (alreadyAttacked.find({A, B}) == alreadyAttacked.end()) {
                    
				applyDamage(entityA, entityB);
				applyDamage(entityB, entityA);
            
            	alreadyAttacked.insert({A, B});
        	}
		}
	}
}

void DamageSystem::applyDamage(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target) {
    if (attacker->hasComponent<DamageComponent>() && target->hasComponent<StatusComponent>()
    	&& attacker->hasComponent<TeamTag>() && target->hasComponent<TeamTag>()) {
        auto attackComp = attacker->getComponent<DamageComponent>();
        auto statusComp = target->getComponent<StatusComponent>();
        auto teamCompA = attacker->getComponent<TeamTag>();
        auto teamCompT = target->getComponent<TeamTag>();

        if(!statusComp->alive) return;

        if(teamCompA->teamCode == teamCompT->teamCode) return;

	    if (attackComp->hitTargets.count(target->getID()) == 0) {

	    	if(target->hasComponent<StateComponent>()){
	    		auto stateComp = target->getComponent<StateComponent>();
	    		stateComp->changeState(States::Hurt, 0.7f);
	    	}

	        statusComp->currentHp -= attackComp->damage;
	        attackComp->hitTargets.insert(target->getID());

	        std::cout << statusComp->currentHp << "/" << statusComp->maxHp << std::endl;
	        if(statusComp->currentHp <= 0){
	        	statusComp->currentHp = 0;
		        if(target->hasComponent<StateComponent>()){
		    		auto stateComp = target->getComponent<StateComponent>();
		    		stateComp->changeState(States::Death, 1.0f);
		    	}
	        	statusComp->alive = false;
	        	std::cout << "Died" << std::endl;
	        }
	    } 
    }
}
