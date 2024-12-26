#include "Events/EventSystem.h"
#include "Components/PositionComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/StateComponent.h"
#include "Components/CommandComponent.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include <iostream>
#include <string>


void EventSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	Event evt;
	while(eventManager->pollEvent(evt)){
		handleEvent(evt, entities);
	}


}

void EventSystem::handleEvent(const Event& evt, std::vector<std::shared_ptr<Entity>>& entities){


// if(evt.type == EventType::KEYDOWN || evt.type == EventType::KEYUP){
// 		if(isControlKey(evt.key)){
// 	}
// 	}
	// Find Target
	
			for(auto& entity : entities){
				if(entity->hasComponent<PlayableComponent>() && entity->hasComponent<CommandComponent>()){


					auto playComp = entity->getComponent<PlayableComponent>();
					auto commandComp = entity->getComponent<CommandComponent>();



					if(playComp&&commandComp){

						if(evt.type == EventType::KEYDOWN){
							if(isControlKey(evt.key)){
								pressed[toInt(evt.key)] = true;
								if(isArrow(evt.key)){
									if(isHorizontal(evt.key)){
										lastHorizontalKey = evt.key;
										if(evt.key == KeyCode::Left){
											std::cout << "Left" << std::endl;					
											commandComp->commandData.moveDirection.hDir = -1;
										}else{
											std::cout << "Right" << std::endl;
											commandComp->commandData.moveDirection.hDir = 1;
										}
									}

									if(isVertical(evt.key)){
										lastVerticalKey = evt.key;
										if(evt.key == KeyCode::Up){
											std::cout << "Up" << std::endl;
											commandComp->commandData.moveDirection.vDir = -1;
										}else{
											std::cout << "Down" << std::endl;
											commandComp->commandData.moveDirection.vDir = 1;
										}
									}
								
									commandComp->commandData.type = CommandType::Move;
									

								}
							}
						}

						if(evt.type == EventType::KEYUP){

							pressed[toInt(evt.key)] = false;
							std::cout << "KeyUp : ";
							if(isHorizontal(evt.key)){

								// Set moveDirection
								if(pressed[toInt(KeyCode::Left)] && !pressed[toInt(KeyCode::Right)] ){
									commandComp->commandData.moveDirection.hDir = -1;
								}

								if(!pressed[toInt(KeyCode::Left)] && pressed[toInt(KeyCode::Right)] ){
									commandComp->commandData.moveDirection.hDir = 1;
								}


								if(!pressed[toInt(KeyCode::Left)] && !pressed[toInt(KeyCode::Right)] ){
									commandComp->commandData.moveDirection.hDir = 0;
								}


								// Set Up key
								if(evt.key == KeyCode::Left){
									std::cout << "Left" << std::endl;
									if(pressed[toInt(KeyCode::Right)]) lastVerticalKey = KeyCode::Right;
								}
								if(evt.key == KeyCode::Right){
									std::cout << "Right" << std::endl;
									if(pressed[toInt(KeyCode::Left)]) lastVerticalKey = KeyCode::Left;
								}

							}
							if(isVertical(evt.key)){
								if(pressed[toInt(KeyCode::Up)] && !pressed[toInt(KeyCode::Down)] ){
									commandComp->commandData.moveDirection.vDir = -1;
								}

								if(!pressed[toInt(KeyCode::Up)] && pressed[toInt(KeyCode::Down)] ){
									commandComp->commandData.moveDirection.vDir = 1;
								}


								if(!pressed[toInt(KeyCode::Up)] && !pressed[toInt(KeyCode::Down)] ){
									commandComp->commandData.moveDirection.vDir = 0;
								}
							}

								
							

							if(evt.key == KeyCode::Up){
								std::cout << "Up" << std::endl;
								if(pressed[toInt(KeyCode::Down)]) lastVerticalKey = KeyCode::Down;
							}

							if(evt.key == KeyCode::Down){
								std::cout << "Down" << std::endl;
								if(pressed[toInt(KeyCode::Up)]) lastVerticalKey = KeyCode::Up;
							}

								
						}
						if(!pressed[toInt(KeyCode::Right)] && !pressed[toInt(KeyCode::Left)] && !pressed[toInt(KeyCode::Down)] && !pressed[toInt(KeyCode::Up)]){
								commandComp->commandData.type = CommandType::None;
								
						}
					}

					if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Space) {
				        
				        commandComp->commandData.type = CommandType::Attack;

				        
				    }







				}
			}

		

	

	


	



	if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Enter) {
        Event sceneChangeEvent;
        sceneChangeEvent.type = EventType::SCENE_CHANGE;
        sceneChangeEvent.sceneChangeData = SceneChangeEventData{"GameplayScene"};
        eventManager->pushBigEvent(sceneChangeEvent);
    }

    if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Escape) {

    	for(auto& entity : entities){
			auto posComp = entity->getComponent<PositionComponent>();
			auto playComp = entity->getComponent<PlayableComponent>();
			auto stateComp = entity->getComponent<StateComponent>();			
			if(posComp && playComp){
				std::cout << "(" << posComp->x() << ", " << posComp->y() << ")" ;
			}
			if(stateComp && playComp){
				if(stateComp->currentState == States::Idle) std::cout << "Idle" << std::endl;
				if(stateComp->currentState == States::Attack) std::cout << "Attack" << std::endl;
				
			}
		}
    }
}












bool EventSystem::isControlKey(const KeyCode& key){

	if(key == KeyCode::Up ||
		key == KeyCode::Down ||
		key == KeyCode::Left ||
		key == KeyCode::Right ||
		key == KeyCode::Space)
	{
		return true;
	}

	return false;
}


bool EventSystem::isArrow(const KeyCode& key){
	if(key == KeyCode::Up || key == KeyCode::Down || key == KeyCode::Left || key == KeyCode::Right) return true;
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
// bool left, right, up, down;



// 	if(evt.type == EventType::KEYDOWN){
// 		std::cout << "KEYDOWN" << std::endl;

// 		for(auto& entity : entities){

// 			auto trans = entity->getComponent<TransformComponent>();
// 			bool playable = entity->hasComponent<PlayableComponent>();

// 			if(trans && playable){
// 				if(evt.key == KeyCode::Left){
// 					trans->setDirectionX(-1);
// 					left = true;
// 				}
// 				if(evt.key == KeyCode::Right){
// 					trans->setDirectionX(1);
// 					right = true;
// 				}
// 				if(evt.key == KeyCode::Up){
// 					trans->setDirectionY(-1);
// 					up = true;
// 				}
// 				if(evt.key == KeyCode::Down){
// 				 	trans->setDirectionY(1);
// 				 	down = true;
// 				}
// 			}

// 			if(trans && playable){
// 				if(left || right || up || down){
// 					trans->setMoving(true);
// 				}
// 			}

// 		}
// 	}

// 	if(evt.type == EventType::KEYUP){

// 		std::cout << "KEYUP"  << std::endl;

// 		for(auto& entity : entities){

// 			auto trans = entity->getComponent<TransformComponent>();
// 			bool playable = entity->hasComponent<PlayableComponent>();

// 			if(trans && playable){
// 				if(evt.key == KeyCode::Left && trans->direction.x == -1) trans->setDirectionX(0);
// 				if(evt.key == KeyCode::Right && trans->direction.x == 1) trans->setDirectionX(0);	
// 				if(evt.key == KeyCode::Up && trans->direction.y == -1)	trans->setDirectionY(0);
// 				if(evt.key == KeyCode::Down && trans->direction.y == 1) trans->setDirectionY(0);

// 				if(evt.key == KeyCode::Left) left = false;
// 				if(evt.key == KeyCode::Right) right = false;	
// 				if(evt.key == KeyCode::Up) up = false;
// 				if(evt.key == KeyCode::Down) down = false;

// 				if(!left && !right & !up && !down){
// 					trans->setMoving(false);
// 				}
// 			}
// 		}

// 	}