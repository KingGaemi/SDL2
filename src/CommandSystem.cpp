#include "Systems/CommandSystem.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/CommandComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/CooldownComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/ActionComponent.h"
#include <iostream>



void CommandSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){


	for(auto& entity : entities){

		if(entity){

			if(entity->isActive &&
			  (entity->hasComponent<CommandComponent>() ||
			   entity->hasComponent<MovementCommandComponent>())){

				auto commandComp = entity->getComponent<CommandComponent>();				
				// auto directComp = entity->getComponent<DirectionComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto stateComp = entity->getComponent<StateComponent>();
				

				if(statusComp && stateComp){

					if(commandComp){
						Command command = commandComp->pop();
						if(command.commandType == CommandType::BasicAttack){		
							if(!stateComp->inMotion || (stateComp->actionState == ActionStates::Hurt)){
								if(!command.doubleTap){
									stateComp->changeActionState(ActionStates::Attack, (1.0f / statusComp->attackSpeed));
									AttackEvent attackEvent;
									attackEvent.attackerId = entity->getId();
									attackEvent.attackType = AttackType::Attack;
									eventManager->pushAttackEvent(attackEvent);
									// // std::cout << cooldownComp->cooldownAbilities["attack"].cooldownTime << std::endl;
									// cooldownComp->resetCooldown("basicAttack");
								}else{
									stateComp->changeActionState(ActionStates::SpecialAttack, (1.0f / statusComp->attackSpeed));
									
									// std::cout << cooldownComp->cooldownAbilities["attack"].cooldownTime << std::endl;			
								}
							}else{

							}
						}else if(command.commandType == CommandType::Cast){
							if(!stateComp->inMotion) stateComp->changeActionState(ActionStates::Cast, (1.0f / statusComp->attackSpeed));
							AttackEvent attackEvent;
							attackEvent.attackerId = entity->getId();
							attackEvent.attackType = AttackType::Cast;
							attackEvent.abilityId = command.abilityNumber;
							eventManager->pushAttackEvent(attackEvent);
						}else if(command.commandType == CommandType::Shoot){
							if(!stateComp->inMotion) stateComp->changeActionState(ActionStates::Attack, (1.0f / statusComp->attackSpeed));
							AttackEvent attackEvent;
							attackEvent.attackerId = entity->getId();
							attackEvent.attackType = AttackType::Shoot;
							eventManager->pushAttackEvent(attackEvent);
						}else{
							stateComp->changeActionState(ActionStates::Idle, 0);
						}
					}
				}
			}
		}
	}
}