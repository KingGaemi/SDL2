#include "Systems/DamageSystem.h"
#include "Components/DamageComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/ShakeEffectComponent.h"
#include "Groups.h"
#include <iostream>
#include <cmath>




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

	// find entity with DamageComponent
    if (attacker->hasComponent<DamageComponent>() && target->hasComponent<StatusComponent>()
    	&& attacker->hasComponent<TeamTag>() && target->hasComponent<TeamTag>()) {
        auto damageComp = attacker->getComponent<DamageComponent>();
        auto statusComp = target->getComponent<StatusComponent>();
        auto teamCompA = attacker->getComponent<TeamTag>();
        auto teamCompT = target->getComponent<TeamTag>();
		
        if(!statusComp->isAlive) return;
        if(teamCompA->teamCode == teamCompT->teamCode) return;
	    if(damageComp->hitTargets.count(target->getId()) != 0) return;


		// shake target in proportion to damage
	    if(target->hasComponent<ShakeEffectComponent>()){
    		auto shakeComp = target->getComponent<ShakeEffectComponent>();
    		int maxHp = statusComp->maxHp;
    		// float amount = static_cast<float>(damageComp->damage)/maxHp;
    		float amount = log(static_cast<float>(damageComp->damage) + 1) / log(static_cast<float>(maxHp) + 1);
    		shakeComp->shakeTime = 0.5f;
    		shakeComp->shakeAmount = amount * 3.5f;
    		// if(shakeComp->shakeAmount >= )
    	}

    	// if(target->hasComponent<StateComponent>()){
    	// 	auto stateComp = target->getComponent<StateComponent>();
    	// 	stateComp->changeActionState(ActionStates::Hurt, 0.7f);
    	// }

		// calculate damage(int)

        statusComp->takeDamage(damageComp->damage);
        damageComp->hitTargets.insert(target->getId());

        if(attacker->hasComponent<SoundEffectComponent>() && target->hasComponent<SoundEffectComponent>()){
        	auto attackerSound = attacker->getComponent<SoundEffectComponent>();
        	auto attackerMaterial = attackerSound->bodyMaterial;
        	auto targetSound = target->getComponent<SoundEffectComponent>();
        	auto targetMaterial = targetSound->bodyMaterial;

        	soundManager->playEffect(attackerMaterial + "_" + damageComp->attackType + "_" + targetMaterial);
        }
        
        if(attacker->hasComponent<ProjectileComponent>()){
        	auto projectileComp = attacker->getComponent<ProjectileComponent>();
        	projectileComp->penetration -= 1;
        	if(projectileComp->penetration < 0)  attacker->terminate = true;
        }
        
        auto moveCommandComp = target->getComponent<MovementCommandComponent>();


		// Temporarily Impulse deleted;
		// if(moveCommandComp) {
		// 	MovementCommand moveCommand;
		// 	moveCommand.moveCommandType = MovementCommandType::Impulse;
		// 	moveCommand.force = damageComp->knockBackForce;
		// 	if(attacker->hasComponent<TransformComponent>()) {
		// 		auto transComp = attacker->getComponent<TransformComponent>();
		// 		if(transComp){
		// 			moveCommand.radian = transComp->radian;						
		// 		}
		// 	}
		// 	moveCommandComp->push(moveCommand);
		// }


        if(statusComp->currentHp <= 0){
        	statusComp->currentHp = 0;
	        if(target->hasComponent<StateComponent>()){
	    		auto stateComp = target->getComponent<StateComponent>();
	    		auto moveCommandComp = target->getComponent<MovementCommandComponent>();
	    		if(moveCommandComp) {
	    			MovementCommand moveCommand;
	    			moveCommand.direction = {0, 0};
	    			moveCommand.moveCommandType = MovementCommandType::Hold;
	    			moveCommandComp->push(moveCommand);
	    		}
	    		if(stateComp) stateComp->changeActionState(ActionStates::Death, 0.8f);
        		getReward(attacker, target);
        		if(target->hasComponent<SoundEffectComponent>()){
        			auto targetSound = target->getComponent<SoundEffectComponent>();
        			auto targetType = targetSound->typeMaterial;
        			soundManager->playEffect(targetType + "_death");
        		}    		
	    	}
			statusComp->isAlive = false;
        }
    }
}

void DamageSystem::getReward(std::shared_ptr<Entity> attacker, std::shared_ptr<Entity> target){

	std::shared_ptr<Entity> killer;
	// std::shared_ptr<Entity>

	if(attacker->hasComponent<ProjectileComponent>()){
    	auto projectileComp = attacker->getComponent<ProjectileComponent>();		        	
		killer = ecsManager->getEntityById(projectileComp->ownerId);
    }else{
    	killer = attacker;
    }

    auto killerStatus = killer->getComponent<StatusComponent>();
    auto targetStatus = target->getComponent<StatusComponent>();
    killerStatus->gainExp(targetStatus->rewardExp);

}