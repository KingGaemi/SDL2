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
				auto moveCommandComp = entity->getComponent<MovementCommandComponent>();
				auto veloComp = entity->getComponent<VelocityComponent>();
				auto directComp = entity->getComponent<DirectionComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto stateComp = entity->getComponent<StateComponent>();
				auto cooldownComp = entity->getComponent<CooldownComponent>();

				if(veloComp && directComp && statusComp && stateComp && cooldownComp){
					if(commandComp){
						auto command = commandComp->pop();
						if(command.moveCommandType == MovementCommandType::Move){

							if(stateComp->movementState == MovementStates::Stop){
								stateComp->changeMovementState(MovementStates::Walk);
							}

							if(command.moveDoubleTap){
								stateComp->changeMovementState(MovementStates::Run);
							}
							if(stateComp->movementState == MovementStates::Run){
								if((command.moveDir.hDir == -1 && directComp->direction.hDir == 1) ||
									(command.moveDir.hDir == 1 && directComp->direction.hDir == -1) ||
									(command.moveDir.vDir == -1 && directComp->direction.vDir == 1) ||
									(command.moveDir.vDir == 1 && directComp->direction.vDir == -1)){
									stateComp->changeMovementState(MovementStates::Walk);
								} 
							}

							directComp->direction = command.moveDir;
							Vector2D velo = directComp->dirToVector();							
							velo = velo * statusComp->movementSpeed;
							if(stateComp->movementState == MovementStates::Run){
								// std::cout << statusComp->movementSpeed <<std::endl;
								velo = velo * statusComp->runningSpeedMultiple;
							}else{
								// std::cout <<std::endl;
							}

							// Adjust diagonal movement speed
							int dir = directComp->direction.hDir + directComp->direction.vDir;
							if(dir == 0 || dir == 2 || dir == -2){
								velo = velo * 0.8f;
							}
							
							veloComp->set(velo);

						}else if(command.moveCommandType == MovementCommandType::Stop){
							stateComp->changeMovementState(MovementStates::Stop);
							veloComp->zero();							
						}
					}

					if(commandComp){
						Command command = commandComp->pop();
						if(command.actionCommandType == ActionCommandType::BasicAttack){		
							if(!stateComp->inMotion){
								if(!command.actionDoubleTap){
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
						}else if(command.actionCommandType == ActionCommandType::Cast){
							if(!stateComp->inMotion) stateComp->changeActionState(ActionStates::Cast, (1.0f / statusComp->attackSpeed));
							AttackEvent attackEvent;
							attackEvent.attackerId = entity->getId();
							attackEvent.attackType = AttackType::Cast;
							eventManager->pushAttackEvent(attackEvent);
						}else if(command.actionCommandType == ActionCommandType::Shoot){
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