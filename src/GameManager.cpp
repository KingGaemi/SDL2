#include "Manager/GameManager.h"
#include "EffectManager.h"

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

void GameManager::popUpSelectMenu () {

	Event sceneChangeEvent;
    sceneChangeEvent.type = EventType::SCENE_CHANGE;
    sceneChangeEvent.sceneChangeData = SceneChangeEventData{"CharacterSelectScene"};
    if(eventManager) eventManager->pushBigEvent(sceneChangeEvent);
    else std::cout << "eventManager is nullptr" << std::endl;

}

void GameManager::gameOver (int reason) {

    isGameover = true;

    Event pauseEvent; 
    pauseEvent.type = EventType::GAMEOVER;  

    if(eventManager) {
        eventManager->pushBigEvent(pauseEvent);
        std::cout << "GAME OVER" << std::endl;
    }else{
        std::cout << "eventManager is nullptr" << std::endl;
    }

    if(reason == 1){
        std::cout << "You died.." << std::endl;
        
    }else if(reason == 2){
        std::cout << "Core destroyed.." << std::endl;

    }else if(reason == 3){
        std::cout << "Stage clear" << std::endl;

    }
}

SceneCode GameManager::getCurrentScene(){

    return currentScene;
}


void GameManager::stageClear () {

    isGameover = true;
    Event pauseEvent; 
    pauseEvent.type = EventType::GAMEOVER;  

    if(eventManager) {
        eventManager->pushBigEvent(pauseEvent);
        std::cout << "Stage Clear" << std::endl;
    }else{
        std::cout << "eventManager is nullptr" << std::endl;
    }

    

}