#include "CharacterSelectScene.h"
#include "ECS/ECSManager.h"
#include <iostream>

void CharacterSelectScene::onEnter() {

	if (this->ecsManager) {
        std::cout << "CharacterSelectScene initialized with a valid manager." << std::endl;
    } else {
        std::cerr << "CharacterSelectScene initialized with a nullptr manager!" << std::endl;
    }



	SpawnRequest req;

	req.entityType = EntityType::UI;
	req.name = "confirm_button";
	req.x = 400;
	req.y = 400;

	ecsManager->pendingSpawns.push_back(req);


}


void CharacterSelectScene::handleEvents(const std::vector<Event>& events){

}


void CharacterSelectScene::render(){

		
}

void CharacterSelectScene::update(float deltaTime){

	// ecsManager->updateSystems(deltaTime);

}



void CharacterSelectScene::onExit(){

 	ecsManager->cleanUpEntitiesByScene(SceneCode::Select);
 }