#include "Systems/CommandSystem.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/CommandComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/CooldownComponent.h"
#include "Components/PlayableComponent.h"
#include <iostream>



void CommandSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){


	for(auto& entity : entities){

		if(entity){

			if(entity->isActive && entity->hasComponent<CommandComponent>()){
				auto commandComp = entity->getComponent<CommandComponent>();
				auto veloComp = entity->getComponent<VelocityComponent>();
				auto directComp = entity->getComponent<DirectionComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto stateComp = entity->getComponent<StateComponent>();
				auto cooldownComp = entity->getComponent<CooldownComponent>();

				if(commandComp && veloComp && directComp && statusComp && stateComp && cooldownComp){

					if(commandComp->commandData.type == CommandType::Move){


						directComp->direction = commandComp->commandData.moveDirection;
						Vector2D velo = directComp->dirToVector();

						int dir = directComp->direction.hDir + directComp->direction.vDir;

						if(dir == 0 || dir == 2 || dir == -2){
							velo = velo * statusComp->movementSpeed * 0.8f;
						}else{
							velo = velo * statusComp->movementSpeed;

						}	

						veloComp->set(velo);

						stateComp->isWalking = true;
						stateComp->isRunning = false;
						stateComp->changeState(States::Walk);

					
					}else if(commandComp->commandData.type == CommandType::Run){

						directComp->direction = commandComp->commandData.moveDirection;
						Vector2D velo = directComp->dirToVector();

						int dir = directComp->direction.hDir + directComp->direction.vDir;

						if(dir == 0 || dir == 2 || dir == -2){
							velo = velo * statusComp->movementSpeed * 0.8f * 2;
						}else{
							velo = velo * statusComp->movementSpeed * 2;

						}	

						veloComp->set(velo);

						stateComp->isWalking = false;
						stateComp->isRunning = true;
						stateComp->changeState(States::Run);


					
					}else if(commandComp->commandData.type == CommandType::None){


						veloComp->zero();
						
						stateComp->isRunning = false;
						stateComp->isWalking = false;
						stateComp->changeState(States::Idle);

					}

					if(commandComp->commandData.type == CommandType::Attack && cooldownComp->isOnCooldown("basicAttack")){

						directComp->direction = commandComp->commandData.moveDirection;
						
						// Vector2D velo = directComp->dirToVector();

						// velo = velo * statusComp->movementSpeed;

						// veloComp->set(velo);

						if(!stateComp->inMotion){
							stateComp->changeState(States::Attack, cooldownComp->cooldownAbilities["basicAttack"].cooldownTime);
							// std::cout << cooldownComp->cooldownAbilities["attack"].cooldownTime << std::endl;
							cooldownComp->resetCooldown("basicAttack");
						}
						
					}
				}
			}
		}
	}
}