#include "GameplayScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"
#include "KeyCode.h"
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

	for (auto event : events){
		if(event.type == "KEYDOWN"){
			
			if (event.key == KeyCode::Right) {
                ecsManager->setVelocity(player, 1, 0);  // 오른쪽으로 이동
            } else if (event.key == KeyCode::Left) {
                ecsManager->setVelocity(player, -1, 0); // 왼쪽으로 이동
            } else if (event.key == KeyCode::Up) {
                ecsManager->setVelocity(player, 0, -1);  // 위로 이동
            } else if (event.key == KeyCode::Down) {
                ecsManager->setVelocity(player, 0, 1); // 아래로 이동
            }
      
		}
		
	}

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
