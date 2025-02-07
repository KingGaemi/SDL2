#include "Events/EventSystem.h"
#include "Components/PositionComponent.h"

#include "Components/PlayableComponent.h"
// #include "Components/StateComponent.h"
#include "Components/CommandComponent.h"
#include "Components/MovementCommandComponent.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "Groups.h"
#include <iostream>
#include <string>


void EventSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	if(leftDoubleTapTime > 0){
		leftDoubleTapTime -= deltaTime;
	}else{
		leftDoubleTapTime = 0;
	}

	Event evt;
	eventManager->pollEvent(evt);
	handleEvent(evt, entities);

}

void EventSystem::handleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>& entities){

	// Check KeyDowns and direction
	if(evt.type == EventType::KEYDOWN && !pressed[toInt(evt.key)]){
		pressed[toInt(evt.key)] = true;
		// std::cout << toInt(evt.key) << std::endl;
		if(evt.key == lastArrowKey && leftDoubleTapTime > 0 ){
			isArrowKeyDoubleTapped = true;
		}else if(evt.key == lastAbilityKey && leftDoubleTapTime > 0 ){
			isAbilityKeyDoubleTapped = true;
		}else{
			leftDoubleTapTime = doubleTapTime;
			isArrowKeyDoubleTapped = false;
			isAbilityKeyDoubleTapped = false;
		}
	}
	if(evt.type == EventType::KEYUP) pressed[toInt(evt.key)] = false;
  	direction = getDirection(evt);
	
	// Find Target
	for(auto& entity : entities){
		if(entity->isActive &&
			entity->hasComponent<PlayerTag>() &&
			entity->hasComponent<PlayableComponent>() &&
			(entity->hasComponent<CommandComponent>() || entity->hasComponent<MovementCommandComponent>())){

			targetEntity = entity;
		}
	}
	//==========================
	// KeyDown to commands
	//


	// temp ====
	if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Enter) {
        Event sceneChangeEvent;
        sceneChangeEvent.type = EventType::SCENE_CHANGE;
        sceneChangeEvent.sceneChangeData = SceneChangeEventData{"GameplayScene"};
        eventManager->pushBigEvent(sceneChangeEvent);
    }
    // ======


	if(!targetEntity) return;
	auto commandComp = targetEntity->getComponent<CommandComponent>();
	auto moveCommandComp = targetEntity->getComponent<MovementCommandComponent>();

	if(moveCommandComp){
		MovementCommand moveCommand;
		moveCommand.direction = direction;
		moveCommand.doubleTap = isArrowKeyDoubleTapped;				
		if(arrowIsPressed()){
			moveCommand.moveCommandType = MovementCommandType::MoveToDirection;
		}else{
			moveCommand.moveCommandType = MovementCommandType::Stop;
		}
		moveCommandComp->push(moveCommand);
	}

	if(commandComp){
		Command command;
		command.doubleTap = isAbilityKeyDoubleTapped;
		// attack is pressed
		if(pressed[toInt(KeyCode::Space)]){
			// std::cout << "space" << std::endl;
			command.commandType = CommandType::BasicAttack;
			commandComp->push(command);
		}
		if(pressed[toInt(KeyCode::q)]){
			// std::cout << "q" << std::endl;
			command.abilityNumber = 1;
			command.commandType = CommandType::Cast;
			command.direction = {0,0};
			commandComp->push(command);
		}
		if(pressed[toInt(KeyCode::w)]){	
			// std::cout << "w" << std::endl;		
			command.abilityNumber = 2;
			command.commandType = CommandType::Shoot;
			command.direction = {0,0};
			commandComp->push(command);
		}
		if(pressed[toInt(KeyCode::e)]){	
			// std::cout << "w" << std::endl;		
			command.abilityNumber = 3;
			command.commandType = CommandType::Cast;
			commandComp->push(command);
		}	
	}
		
///=============================================================================

	// if(pressed[toInt(KeyCode::q)]){
	// 	if(commandComp){
	// 		Command command;
	// 		command.abilityNumber = 1;
	// 		command.commandType = CommandType::Cast;
	// 		command.direction = {0,0};
	// 		commandComp->push(command);
	// 	}
	// }
	// if(pressed[toInt(KeyCode::w)]){
	// 	if(commandComp){
	// 		Command command;
	// 		command.abilityNumber = 2;
	// 		command.commandType = CommandType::Shoot;
	// 		command.direction = {0,0};
	// 		commandComp->push(command);
	// 	}
	// }
}

// helper function
Direction EventSystem::getDirection(const Event& evt){

	if(evt.type == EventType::KEYDOWN){	
		if(isArrowKey(evt.key)){
			lastArrowKey = evt.key;
			if(isHorizontal(evt.key)) lastHorizontalKey = evt.key;
			else if(isVertical(evt.key)) lastVerticalKey = evt.key;		
		}
	}	
           
	if(evt.type == EventType::KEYUP){
		if(isArrowKey(evt.key)){
			// std::cout << "KeyUp : ";
			if(evt.key == KeyCode::Left){
				// std::cout << "Left" << std::endl;
				if(pressed[toInt(KeyCode::Right)]) lastHorizontalKey = KeyCode::Right;
			}else if(evt.key == KeyCode::Right){
				// std::cout << "Right" << std::endl;
				if(pressed[toInt(KeyCode::Left)]) lastHorizontalKey = KeyCode::Left;
			}else if(evt.key == KeyCode::Up){
				// std::cout << "Up" << std::endl;
				if(pressed[toInt(KeyCode::Down)]) lastVerticalKey = KeyCode::Down;
			}else if(evt.key == KeyCode::Down){
				// std::cout << "Down" << std::endl;
				if(pressed[toInt(KeyCode::Up)]) lastVerticalKey = KeyCode::Up;
			}
		}
	}

	// Set direction
	if(pressed[toInt(KeyCode::Left)] && lastHorizontalKey == KeyCode::Left) direction.hDir = -1;
	if(pressed[toInt(KeyCode::Right)] && lastHorizontalKey == KeyCode::Right) direction.hDir = 1;
	if(!pressed[toInt(KeyCode::Right)] && !pressed[toInt(KeyCode::Left)]) direction.hDir = 0;

	if(pressed[toInt(KeyCode::Up)] && lastVerticalKey == KeyCode::Up) direction.vDir = -1;
	if(pressed[toInt(KeyCode::Down)] && lastVerticalKey == KeyCode::Down) direction.vDir = 1;
	if(!pressed[toInt(KeyCode::Up)] && !pressed[toInt(KeyCode::Down)]) direction.vDir = 0;

	// When all arrow keys up
	if(!pressed[toInt(KeyCode::Left)] &&
	   !pressed[toInt(KeyCode::Right)] &&
	   !pressed[toInt(KeyCode::Up)] &&
	   !pressed[toInt(KeyCode::Down)]){
   		// follow last arrow key
		if(lastArrowKey == KeyCode::Left) direction.hDir = -1;
		else if(lastArrowKey == KeyCode::Right) direction.hDir = 1;
		else if(lastArrowKey == KeyCode::Up) direction.vDir = -1;
		else if(lastArrowKey == KeyCode::Down) direction.vDir = 1;
	}
	return direction;		
}





















// checker function

bool EventSystem::checkArrowKeyDoubleTapped(const Event& evt){
	if(!isArrowKey(evt.key)) return false;
	if(evt.key == lastArrowKey && leftDoubleTapTime >= 0 ) return true;
	return false;
}


bool EventSystem::checkAbilityKeyDoubleTapped(const Event& evt){
	if(!isAbilityKey(evt.key)) return false;
	if(evt.key == lastAbilityKey && leftDoubleTapTime >= 0 ) return true;	
	if(evt.type == EventType::KEYDOWN) lastAbilityKey = evt.key;
	return false;
}

bool EventSystem::arrowIsPressed(){
	if(pressed[toInt(KeyCode::Left)] || pressed[toInt(KeyCode::Right)] || pressed[toInt(KeyCode::Up)] || pressed[toInt(KeyCode::Down)]){
		return true;
	}
	return false;
}

bool EventSystem::isArrowKey(const KeyCode& key){
	if(key == KeyCode::Up || key == KeyCode::Down || key == KeyCode::Left || key == KeyCode::Right) return true;
	return false;
}
bool EventSystem::isAbilityKey(const KeyCode& key){
	if(key == KeyCode::Space ||
		key == KeyCode::q ||
		key == KeyCode::w ||
		key == KeyCode::e ||
		key == KeyCode::r) return true;
	return false;
}
	
bool EventSystem::isHorizontal(const KeyCode& key){
	if(key == KeyCode::Left || key == KeyCode::Right) return true;
	return false;
}

bool EventSystem::isVertical(const KeyCode& key){
	if(key == KeyCode::Up || key == KeyCode::Down) return true;
	return false;
}

bool EventSystem::isAttack(const KeyCode& key){
	if(key == KeyCode::Space) return true;
	return false;
}

