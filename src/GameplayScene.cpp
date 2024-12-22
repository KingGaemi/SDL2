#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "KeyCode.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){


	SpawnRequest req1;
	SpawnRequest req2;

	req1.type = "player";
	req1.x = 100.0f;
	req1.y = 150.0f;

	ecsManager->pendingSpawns.push_back(req1);

	req2.type = "farmer";
	req2.x = 500.0f;
	req2.y = 600.0f;
	ecsManager->pendingSpawns.push_back(req2);


	player = ecsManager->getEntityByName("player");
	farmer = ecsManager->getEntityByName("farmer");

	
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


	if(player) player->isActive = false;
	if(farmer) farmer->isActive = false;


}
