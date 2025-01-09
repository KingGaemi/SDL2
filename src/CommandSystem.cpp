#include "Systems/CommandSystem.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/CommandComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/CooldownComponent.h"
#include "Components/PlayableComponent.h"
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
					
					if(moveCommandComp){
						if(moveCommandComp->moveCommandType == MovementCommandType::Move){

							if(stateComp->movementState == MovementStates::Stop){
								stateComp->changeMovementState(MovementStates::Walk);
							}

							if(moveCommandComp->doubleTap){
								stateComp->changeMovementState(MovementStates::Run);
							}
							if(stateComp->movementState == MovementStates::Run){
								if((moveCommandComp->direction.hDir == -1 && directComp->direction.hDir == 1) ||
									(moveCommandComp->direction.hDir == 1 && directComp->direction.hDir == -1) ||
									(moveCommandComp->direction.vDir == -1 && directComp->direction.vDir == 1) ||
									(moveCommandComp->direction.vDir == 1 && directComp->direction.vDir == -1)){
									stateComp->changeMovementState(MovementStates::Walk);
								} 
							}


							directComp->direction = moveCommandComp->direction;
							Vector2D velo = directComp->dirToVector();							
							velo = velo * statusComp->movementSpeed;
							if(stateComp->movementState == MovementStates::Run){
								velo = velo * statusComp->runningSpeed;
							}

							// Adjust diagonal movement speed
							int dir = directComp->direction.hDir + directComp->direction.vDir;
							if(dir == 0 || dir == 2 || dir == -2){
								velo = velo * 0.8f;
							}

							veloComp->set(velo);

						}else if(moveCommandComp->moveCommandType == MovementCommandType::Stop){
							stateComp->changeMovementState(MovementStates::Stop);
							veloComp->zero();							
						}
					}

				if(commandComp){
						if(commandComp->commandType == CommandType::BasicAttack && cooldownComp->isOnCooldown("basicAttack")){
		
							// directComp->direction = commandComp->commandData.moveDirection;
							
							// Vector2D velo = directComp->dirToVector();
		
							// velo = velo * statusComp->movementSpeed;
		
							// veloComp->set(velo);
		
							if(!stateComp->inMotion){
								stateComp->changeActionState(ActionStates::Attack, cooldownComp->cooldownAbilities["basicAttack"].cooldownTime);
								// std::cout << cooldownComp->cooldownAbilities["attack"].cooldownTime << std::endl;
								cooldownComp->resetCooldown("basicAttack");
							}
						}else{
							stateComp->changeActionState(ActionStates::Idle, 0);
						}
						// else if(commandComp->commandType == CommandType::SpecialAttack && cooldownComp->isOnCooldown("specialAttack")){
		
						// 	// directComp->direction = commandComp->commandData.moveDirection;
							
						// 	// Vector2D velo = directComp->dirToVector();
		
						// 	// velo = velo * statusComp->movementSpeed;
		
						// 	// veloComp->set(velo);
		
						// 	if(!stateComp->inMotion){
						// 		stateComp->changeState(States::Attack, cooldownComp->cooldownAbilities["specialAttack"].cooldownTime);
						// 		// std::cout << cooldownComp->cooldownAbilities["attack"].cooldownTime << std::endl;
						// 		cooldownComp->resetCooldown("specialAttack");
						// 	}
						// }
					}
				}
			}
		}
	}
}