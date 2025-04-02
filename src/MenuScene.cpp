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

	SpawnRequest req;

	req.entityType = EntityType::UI;
	req.name = "background";
	req.x = 640.0f;
	req.y = 400.0f;
	// req.hasPosition = true;
	req.w = 1280;
	req.h = 800;
	req.sc = 1.0f;
	
	ecsManager->pendingSpawns.push_back(req);


	req.entityType = EntityType::UI;
	req.name = "select_frame";
	req.w = 192;
	req.h = 32;
	req.sc = 3.0f;
	req.hasTransform = true;
	ecsManager->pendingSpawns.push_back(req);


	
}



void MenuScene::handleEvents(const std::vector<Event>& events){

}


void MenuScene::render(){

		
}

void MenuScene::update(float deltaTime){

	// ecsManager->updateSystems(deltaTime);

}



void MenuScene::onExit(){

 	ecsManager->cleanUpEntitiesByScene(SceneCode::Menu);
 }