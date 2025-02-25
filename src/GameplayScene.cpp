#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "KeyCode.h"
#include "Groups.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){

	if(mapManager) mapManager->loadMap("maps/newResol.tmj");
	SpawnRequest req;

	// req.entityType = EntityType::Unit;
	// req.name = "player";
	// req.x = 145.0f;
	// req.y = 150.0f;
	// req.hasTransform = false;
	// req.teamCode = TeamCode::Ally;
	// ecsManager->pendingSpawns.push_back(req);


	req.entityType = EntityType::Camera;
	req.name = "camera";
	ecsManager->pendingSpawns.push_back(req);
	
	
	req.entityType = EntityType::UI;
	req.name = "hp_bar_frame";
	req.x = 640; // SCREEN_WIDTH/2;
	req.y = 740; 
	ecsManager->pendingSpawns.push_back(req);

	req.entityType = EntityType::UI;
	req.name = "hp_bar_gage";
	req.x = 640; // SCREEN_WIDTH/2;
	req.y = 740; 
	ecsManager->pendingSpawns.push_back(req);


	// auto mapSystem = ecsManager->getSystem<MapSystem>();
	// mapSystem->init();  
	// ecsManager->activeMapEntity();

	std::cout << "GameplayScene initialized!" << std::endl;

}



void GameplayScene::handleEvents(const std::vector<Event>& events){

}

void GameplayScene::render(){	

}

void GameplayScene::update(float deltaTime){

	// ecsManager->updateSystems(deltaTime);	
}

void GameplayScene::onExit(){
	
	ecsManager->cleanUpEntitiesByScene(SceneCode::Game);
	
}
