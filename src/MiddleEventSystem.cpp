#include "Events/MiddleEventSystem.h"
#include "Components/PlayableComponent.h"
#include "Components/CommandComponent.h"
#include "Groups.h"
#include "ECS/Entity.h"
#include <iostream>
#include <string>


void MiddleEventSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	Event evt;
	while(eventManager->pollMiddleEvent(evt)){
		handleMiddleEvent(evt, entities);
	}


}

void MiddleEventSystem::handleMiddleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>& entities){

	if(evt.type == EventType::CHARACTER_CHANGE) {
		std::cout << "CHARACTER_CHANGE" << std::endl;
		for(auto& entity: entities){

			if(entity->hasComponent<PlayerTag>() && 
				entity->hasComponent<PlayableComponent>() && 
				entity->hasComponent<CommandComponent>()) {
				player1 = entity;
			}	
			if(entity->hasComponent<Player2Tag>() && 
				entity->hasComponent<CommandComponent>()) {
				player2 = entity;
			}

		}		
		if (!player1 || !player2) {
		    std::cerr << "Error: player1 or player2 not found!" << std::endl;
		    return; // 또는 적절한 에러 처리
		}else{
			auto commandComp = player1->getComponent<CommandComponent>();
			if(commandComp)
			{
				commandComp->commandType = CommandType::None;
			}

			// Step 1: player1의 컴포넌트 변경
			// if(player2->hasComponent<PlayerTag>()) player2->removeComponent<PlayerTag>();
			player1->removeComponent<PlayerTag>();
			player1->removeComponent<PlayableComponent>();
			player1->addComponent<Player2Tag>();

			// Step 2: player2의 컴포넌트 변경
			// if(player2->hasComponent<PlayerTag>()) player2->removeComponent<PlayerTag>();
			player2->removeComponent<Player2Tag>();
			player2->addComponent<PlayerTag>();
			player2->addComponent<PlayableComponent>();

			if(player1->hasComponent<Player2Tag>() && player2->hasComponent<PlayerTag>() && player2->hasComponent<PlayableComponent>()){
				std::cout << "Success to switch" << std::endl;
			}else{
				player1->addComponent<PlayerTag>();
				player1->addComponent<PlayableComponent>();
				player1->removeComponent<Player2Tag>();

				player2->addComponent<Player2Tag>();
				player2->removeComponent<PlayerTag>();
				player2->removeComponent<PlayableComponent>();
			}

		}

		
	}

}






