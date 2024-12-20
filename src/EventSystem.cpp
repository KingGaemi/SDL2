#include "Events/EventSystem.h"
#include "Components/TransformComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/StateComponent.h"
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

	if(evt.type == EventType::KEYDOWN){
		// std::cout << "KEYDOWN" << std::endl;

		for(auto& entity : entities){

			auto trans = entity->getComponent<TransformComponent>();
			auto state = entity->getComponent<StateComponent>();
			bool playable = entity->hasComponent<PlayableComponent>();

			if(playable && trans && state){
				

				if(evt.key == KeyCode::Left){
				trans->setDirectionX(-1);
				trans->setDirectionY(0);
					// if(state->currentState != States::Walk) state->currentState = States::Walk;
				}
				if(evt.key == KeyCode::Right){
					trans->setDirectionX(1);
					trans->setDirectionY(0);
					// if(state->currentState != States::Walk) state->currentState = States::Walk;
				}
				if(evt.key == KeyCode::Up){
					trans->setDirectionY(-1);
					trans->setDirectionX(0);
					// if(state->currentState != States::Walk) state->currentState = States::Walk;
				}
				if(evt.key == KeyCode::Down){
				 	trans->setDirectionY(1);
					trans->setDirectionX(0);
				 	// if(state->currentState != States::Walk) state->currentState = States::Walk;
				}

				if(evt.key == KeyCode::Space){
					state->changeState(States::Attack, 0.57f);
				}


			}



		}
	}

	if(evt.type == EventType::KEYUP){

		// std::cout << "KEYUP"  << std::endl;

		// for(auto& entity : entities){

		// 	auto trans = entity->getComponent<TransformComponent>();
		// 	auto state = entity->getComponent<StateComponent>();
		// 	bool playable = entity->hasComponent<PlayableComponent>();

		// 	if(trans && playable){
		// 		if(evt.key == KeyCode::Left && trans->direction.x == -1) trans->setDirectionX(0);
		// 		if(evt.key == KeyCode::Right && trans->direction.x == 1) trans->setDirectionX(0);	
		// 		if(evt.key == KeyCode::Up && trans->direction.y == -1)	trans->setDirectionY(0);
		// 		if(evt.key == KeyCode::Down && trans->direction.y == 1) trans->setDirectionY(0);
		// 	}

		// 	if(state){
		// 		if(trans->direction.x == 0 && trans->direction.y == 0){
		// 			if(state->currentState != States::Idle) state->currentState = States::Idle;
		// 		}
		// 	}
		// }

	}

	if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Enter) {
        Event sceneChangeEvent;
        sceneChangeEvent.type = EventType::SCENE_CHANGE;
        sceneChangeEvent.sceneChangeData = SceneChangeEventData{"GameplayScene"};
        eventManager->pushBigEvent(sceneChangeEvent);
    }

    if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Escape) {

    	for(auto& entity : entities){
			auto trans = entity->getComponent<TransformComponent>();			
			if(trans){
				std::cout << "(" << trans->x() << ", " << trans->y() << ")" << std::endl;
			}
		}
    }

    if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Space) {

    	for(auto& entity : entities){
			auto state = entity->getComponent<StateComponent>();			
			if(state){
				state->currentState = States::Attack;
			}
		}
    }




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