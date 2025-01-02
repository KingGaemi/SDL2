#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "KeyCode.h"
#include "Groups.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){


	SpawnRequest req;


	req.type = "player";
	req.x = 145.0f;
	req.y = 150.0f;
	req.w = 32;
	req.h = 39;
	req.sc = 2.0f;
	req.teamCode = TeamCode::Ally;
	ecsManager->pendingSpawns.push_back(req);


	req.type = "enemy";
	req.x = 500.0f;
	req.y = 300.0f;
	req.w = 32;
	req.h = 39;
	req.sc = 2.0f;
	req.teamCode = TeamCode::Enemy;
	ecsManager->pendingSpawns.push_back(req);




	req.type = "farmer";
	req.x = 500.0f;
	req.y = 600.0f;
	req.teamCode = TeamCode::Ally;
	ecsManager->pendingSpawns.push_back(req);


	req.type = "eri" ;
	req.x = 200.0f;
	req.y = 200.0f;
	req.teamCode = TeamCode::Enemy;
	ecsManager->pendingSpawns.push_back(req);

	req.type = "text" ;
	req.x = 500.0f;
	req.y = 200.0f;
	ecsManager->pendingSpawns.push_back(req);


	
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
