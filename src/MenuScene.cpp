#include "MenuScene.h"
#include "ECS/ECSManager.h"
#include "ECS/Entity.h"
#include "ECS/EntityFactory.h"


#include <iostream>


// MenuScene::~MenuScene(){

// 	onExit();
// }


void MenuScene::onEnter(){

	if (this->ecsManager) {
        std::cout << "MenuScene initialized with a valid manager." << std::endl;
    } else {
        std::cerr << "MenuScene initialized with a nullptr manager!" << std::endl;
    }


	auto entityFactory = ecsManager->shareFactory();


	if(entityFactory){
		entityFactory->createBackgroundEntity("background_main");
	}else{

		std::cerr << "nullptr factory!" << std::endl;
	}

	background = ecsManager->getEntityByName("background");
	
}



void MenuScene::handleEvents(const std::vector<Event>& events){

}


void MenuScene::render(){

		
}

void MenuScene::update(float deltaTime){

	// ecsManager->updateSystems(deltaTime);

}



void MenuScene::onExit(){

 	background->isActive = false;
 }