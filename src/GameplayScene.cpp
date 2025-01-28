#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "Systems/MapSystem.h"
#include "KeyCode.h"
#include "Groups.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){


	SpawnRequest req;

	req.entityType = EntityType::Unit;
	req.name = "player";
	req.x = 145.0f;
	req.y = 150.0f;
	req.hasTransform = false;
	req.teamCode = TeamCode::Ally;
	ecsManager->pendingSpawns.push_back(req);

	req.entityType = EntityType::Unit;
	req.name = "enemy";
	req.x = 500.0f;
	req.y = 300.0f;
	req.w = 32;
	req.h = 39;
	req.sc = 2.0f;
	req.teamCode = TeamCode::Enemy;
	ecsManager->pendingSpawns.push_back(req);

	req.entityType = EntityType::Unit;
	req.name = "farmer";
	req.x = 500.0f;
	req.y = 600.0f;
	req.w = 21;
	req.h = 28;
	req.sc = 2.0f;
	req.teamCode = TeamCode::Ally;
	ecsManager->pendingSpawns.push_back(req);

	req.entityType = EntityType::Unit;
	req.name = "eri" ;
	req.x = 200.0f;
	req.y = 200.0f;
	req.w = 31;
	req.h = 38;
	req.sc = 2.0f;
	req.teamCode = TeamCode::Enemy;
	ecsManager->pendingSpawns.push_back(req);


	req.entityType = EntityType::UI;
	req.name = "text" ;
	req.x = 500.0f;
	req.y = 200.0f;
	req.w = 100;
	req.h = 50;
	req.sc = 1.0f;
	ecsManager->pendingSpawns.push_back(req);


	req.entityType = EntityType::Object;
	req.name = "ground" ;
	req.x = 640;
	req.y = 775;
	req.w = 1280;
	req.h = 50;
	req.sc = 1.0f;
	ecsManager->pendingSpawns.push_back(req);

	req.entityType = EntityType::Item;
	req.name = "potionCap";
	req.x = 700.0f;
	req.y = 400.0f;
	req.teamCode = TeamCode::Ally;
	ecsManager->pendingSpawns.push_back(req);



	req.entityType = EntityType::Object;
	req.name = "slimeSpawner";
	req.x = 900.0f;
	req.y = 400.0f;
	req.teamCode = TeamCode::Neutral;
	ecsManager->pendingSpawns.push_back(req);


	req.entityType = EntityType::Camera;
	req.name = "camera";
	ecsManager->pendingSpawns.push_back(req);

	
	auto mapSystem = ecsManager->getSystem<MapSystem>();
	mapSystem->init();  
	ecsManager->activeMapEntity();

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
