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


	auto entityFactory = std::make_unique<EntityFactory>();

	std::cout <<"entityFactory created " << std::endl;
	entityFactory->createBackgroundEntity(ecsManager, "background_main");
	
	
}



void MenuScene::handleEvents(const std::vector<Event>& events){
	for (const auto& e : events) {
        if (e.type == "KEYDOWN" && e.key == KeyCode::Enter) {
            std::cout << "Enter Pressed! " << std::endl;
            changeSceneCallback("GameplayScene");
        }
    }
}


void MenuScene::render(){

		
}

void MenuScene::update(float deltaTime){

	ecsManager->updateSystems(deltaTime);

}



void MenuScene::onExit(){

 	// ecsManager->destroyEntity()

}
