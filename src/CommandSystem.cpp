#include "Systems/CommandSystem.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/CommandComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include <iostream>



void CommandSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){


	for(auto& entity : entities){

		if(entity){

			if(entity->hasComponent<CommandComponent>()){
				auto commandComp = entity->getComponent<CommandComponent>();
				auto veloComp = entity->getComponent<VelocityComponent>();
				auto directComp = entity->getComponent<DirectionComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto stateComp = entity->getComponent<StateComponent>();

				if(commandComp && veloComp && directComp && statusComp && stateComp){

					if(commandComp->commandData.type == CommandType::Move){


						directComp->direction = commandComp->commandData.moveDirection;
						
						Vector2D velo = directComp->dirToVector();

						velo = velo * statusComp->movementSpeed;

						veloComp->set(velo);

						stateComp->changeState(States::Walk);

					
					}else if(commandComp->commandData.type == CommandType::None){


						veloComp->zero();

						stateComp->changeState(States::Idle);
					}

					if(commandComp->commandData.type == CommandType::Attack){

						stateComp->callAttack = true;
						stateComp->changeState(States::Attack, 0.57f);

						
					}
				}
			}
		}
	}
}