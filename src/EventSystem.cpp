#include "Events/EventSystem.h"
#include "Components/TransformComponent.h"
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

		std::cout << "KEYDOWN : " << std::endl;

		for(auto& entity : entities){

			auto trans = entity->getComponent<TransformComponent>();
			
			if(trans){

				if(evt.key == KeyCode::Up)	trans->setVel(0, -1);
				if(evt.key == KeyCode::Down) trans->setVel	(0, 1);
				if(evt.key == KeyCode::Right) trans->setVel(1, 0);	
				if(evt.key == KeyCode::Left) trans	->setVel(-1, 0);
			}
		}
	}

	if(evt.type == EventType::KEYUP){

		std::cout << "KEYUP : "  << std::endl;

		for(auto& entity : entities){

			auto trans = entity->getComponent<TransformComponent>();
			
			if(trans){

				if(evt.key == KeyCode::Up)	trans->addVel(0, 1);
				if(evt.key == KeyCode::Down) trans->addVel	(0, -1);
				if(evt.key == KeyCode::Right) trans->addVel(-1, 0);	
				if(evt.key == KeyCode::Left) trans	->addVel(1, 0);
			}
		}

	}

	if (evt.type == EventType::KEYDOWN && evt.key == KeyCode::Enter) {
        Event sceneChangeEvent;
        sceneChangeEvent.type = EventType::SCENE_CHANGE;
        sceneChangeEvent.sceneChangeData = SceneChangeEventData{"GameplayScene"};
        eventManager->pushEvent(sceneChangeEvent);
    }



}

