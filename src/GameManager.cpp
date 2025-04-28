#include "Manager/GameManager.h"
#include "EffectManager.h"
#include "ECS/ECSManager.h"

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

    SpawnRequest req;
    req.entityType = EntityType::UI;
    req.name = "game_over";
    req.x = 1280/2;
    req.y = 800/2;
    req.w = 785;
	req.h = 258;
	req.sc = 0.8f;
    req.hasTransform = true;

    ecsManager->pendingSpawns.push_back(req);
    if(reason == 1){
        std::cout << "You died.." << std::endl;
        
        req.name = "you_died";
        req.x = 1280/2;
        req.y = 660;
        req.w = 300;
        req.h = 120;
        req.sc = 0.4f;
    

    }else if(reason == 2){
        std::cout << "Core destroyed.." << std::endl;

        req.name = "core_destroyed";
        req.x = 1280/2;
        req.y = 660;
        req.w = 300;
        req.h = 120;
        req.sc = 0.4f;

    }else if(reason == 3){
        std::cout << "Stage clear" << std::endl;
        req.x = 1280/2;
        req.y = 660;
        req.w = 300;
        req.h = 120;
        req.sc = 0.4f;
        req.name = "stage_clear";

    }
    ecsManager->pendingSpawns.push_back(req);

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

    SpawnRequest req;
    req.entityType = EntityType::UI;
    req.name = "stage_clear";
    req.x = 1280/2;
    req.y = 800/2;
    req.w = 785;
	req.h = 270;
	req.sc = 0.8f;
    req.hasTransform = true;

    ecsManager->pendingSpawns.push_back(req);
    

}