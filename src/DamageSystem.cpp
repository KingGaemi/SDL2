#include "Systems/DamageSystem.h"
#include "Components/DamageComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Groups.h"
#include <iostream>




void DamageSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	auto& collisionEvents = ecsManager->getCollisionEvents();

	if(!collisionEvents.empty()){
		for(auto& colEvt : collisionEvents){

			auto entityA = colEvt.entityA;
			auto entityB = colEvt.entityB;

			EntityID A = entityA->getId();
        	EntityID B = entityB->getId();

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
        auto damageComp = attacker->getComponent<DamageComponent>();
        auto statusComp = target->getComponent<StatusComponent>();
        auto teamCompA = attacker->getComponent<TeamTag>();
        auto teamCompT = target->getComponent<TeamTag>();

        if(!statusComp->isAlive) return;

        if(teamCompA->teamCode == teamCompT->teamCode) return;

	    if (damageComp->hitTargets.count(target->getId()) == 0) {

	    	if(target->hasComponent<StateComponent>()){
	    		auto stateComp = target->getComponent<StateComponent>();
	    		stateComp->changeActionState(ActionStates::Hurt, 0.7f);
	    	}

	        statusComp->currentHp -= damageComp->damage;
	        damageComp->hitTargets.insert(target->getId());

	        if(attacker->hasComponent<ProjectileComponent>()){
	        	auto projectileComp = attacker->getComponent<ProjectileComponent>();
	        	projectileComp->penetration -= 1;
	        	if(projectileComp->penetration < 0)  attacker->terminate = true;
	        }

	        // std::cout << statusComp->currentHp << "/" << statusComp->maxHp << std::endl;
	        if(statusComp->currentHp <= 0){
	        	statusComp->currentHp = 0;
		        if(target->hasComponent<StateComponent>()){
		    		auto stateComp = target->getComponent<StateComponent>();
		    		auto moveCommandComp = target->getComponent<MovementCommandComponent>();
		    		if(moveCommandComp) {
		    			moveCommandComp->direction = {0, 0};
		    			moveCommandComp->moveCommandType = MovementCommandType::Stop;
		    		}
		    		stateComp->changeActionState(ActionStates::Death, 0.8f);
		    	}
	        	statusComp->isAlive = false;
	        	// std::cout << "Died" << std::endl;
	        }
	    } 
    }
}
