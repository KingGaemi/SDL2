#include "Events/EventSystem.h"
#include "Components/TransformComponent.h"
#include "Components/PlayableComponent.h"
#include "ECS/Entity.h"
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
		std::cout << "KEYDOWN" << std::endl;

		for(auto& entity : entities){

			auto trans = entity->getComponent<TransformComponent>();
			bool playable = entity->hasComponent<PlayableComponent>();

			if(trans && playable){
				if(evt.key == KeyCode::Left) trans->setDirectionX(-1);
				if(evt.key == KeyCode::Right) trans->setDirectionX(1);	
				if(evt.key == KeyCode::Up)	trans->setDirectionY(-1);
				if(evt.key == KeyCode::Down) trans->setDirectionY(1);
			}
		}
	}

	if(evt.type == EventType::KEYUP){

		std::cout << "KEYUP"  << std::endl;

		for(auto& entity : entities){

			auto trans = entity->getComponent<TransformComponent>();
			bool playable = entity->hasComponent<PlayableComponent>();

			if(trans && playable){
				if(evt.key == KeyCode::Left && trans->direction.x == -1) trans->setDirectionX(0);
				if(evt.key == KeyCode::Right && trans->direction.x == 1) trans->setDirectionX(0);	
				if(evt.key == KeyCode::Up && trans->direction.y == -1)	trans->setDirectionY(0);
				if(evt.key == KeyCode::Down && trans->direction.y == 1) trans->setDirectionY(0);
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
			auto trans = entity->getComponent<TransformComponent>();			
			if(trans){
				std::cout << "(" << trans->x() << ", " << trans->y() << ")" << std::endl;
			}
		}
    }




}

