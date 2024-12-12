#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include <iostream>
#include <string>


// GameplayScene::~GameplayScene(){

// 	onExit();
// }


void GameplayScene::onEnter(){

	// std::cout << "GameplayScene init : " << std::endl;
	// Load texture

	auto entityFactory = std::make_unique<EntityFactory>();
	player = entityFactory->createPlayerEntity(ecsManager);
	
	// std::cout << "Player created" << std::endl;


	// std::cout << "setEntityName" << std::endl;
	ecsManager->setEntityName(player, "player_Eri");
	
	
	std::cout << "GameplayScene initialized!" << std::endl;


}



void GameplayScene::handleEvents(const std::vector<Event>& events){

	
	// giveEventsT	oFocus(event);

}





void GameplayScene::render(){
	
   

}

void GameplayScene::update(float deltaTime){
	// handleInput();
	// keyboardController->update();
	ecsManager->updateSystems(deltaTime);	
}

void GameplayScene::onExit(){
	
	// ecsManager->destroyEntity(player);
}
