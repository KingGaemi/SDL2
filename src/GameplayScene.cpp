#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "KeyCode.h"
#include <iostream>
#include <string>




void GameplayScene::onEnter(){

	auto entityFactory = std::make_unique<EntityFactory>();
	player = entityFactory->createPlayerEntity(ecsManager);
	ecsManager->setEntityName(player, "player_orc");
	
	auto farmer = entityFactory->createFarmerEntity(ecsManager);
	ecsManager->setEntityName(farmer, "farmer");	

	
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
	ecsManager->destroyEntity(ecsManager->getEntityByName("player_Eri"));
	ecsManager->destroyEntity(ecsManager->getEntityByName("farmer"));
}
