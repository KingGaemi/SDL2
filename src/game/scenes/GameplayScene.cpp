#include "GameplayScene.h"
#include "ecs/ECSManager.h"
#include "ecs/Entity.h"
#include "ecs/EntityFactory.h"
#include "KeyCode.h"
#include "Groups.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){

	if(mapManager){
		mapManager->loadMap("maps/renew_defense_map.tmj");
		mapManager->enterMap = true;
	}
	SpawnRequest req;

	req.entityType = EntityType::Camera;
	req.name = "camera";
	ecsManager->pendingSpawns.push_back(req);


	std::cout << "GameplayScene initialized!" << std::endl;

}



void GameplayScene::handleEvents(const std::vector<Event>& events){

}

void GameplayScene::render(){	

}

void GameplayScene::update(float deltaTime){

		
}

void GameplayScene::onExit(){
	
	ecsManager->cleanUpEntitiesByScene(SceneCode::Game);
	
}
