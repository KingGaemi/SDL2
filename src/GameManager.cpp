#include "Manager/GameManager.h"
#include <iostream>


void GameManager::gameStart () {


	// load data
	// enter map	

	// change scene
	Event sceneChangeEvent;
    sceneChangeEvent.type = EventType::SCENE_CHANGE;
    sceneChangeEvent.sceneChangeData = SceneChangeEventData{"GameplayScene"};
    if(eventManager) eventManager->pushBigEvent(sceneChangeEvent);
    else std::cout << "eventManager is nullptr" << std::endl;

}

void GameManager::goSelectScene () {

	Event sceneChangeEvent;
    sceneChangeEvent.type = EventType::SCENE_CHANGE;
    sceneChangeEvent.sceneChangeData = SceneChangeEventData{"CharacterSelectScene"};
    if(eventManager) eventManager->pushBigEvent(sceneChangeEvent);
    else std::cout << "eventManager is nullptr" << std::endl;

}