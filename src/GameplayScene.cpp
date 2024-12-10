#include "GameplayScene.h"
#include "Renderer.h"
#include <iostream>
#include <string>




void GameplayScene::init(Renderer* renderer){

	std::cout << "GameplayScene init : " << std::endl;


	// Load texture
	std::string texureID = "eri_copy";
	TextureManager* textureManager = TextureManager::getInstance();	
	if(!textureManager->load(texureID, "res/gfx/eri_copy2.png", renderer)) {
	    std::cout << "Failed to load texture '"<< texureID <<"'" << std::endl;
	    return;
	}


	player = manager->createEntity();
	// std::cout << "Player created" << std::endl;

	playerTransform = &player->addComponent<TransformComponent>(10.0f, 10.0f);
	// std::cout << "add TransfromComponent Complete" << std::endl;
	player->addComponent<SpriteComponent>(texureID, playerTransform, renderer);
	player->addComponent<KeyboardController>(playerTransform);


	std::cout << "setEntityName" << std::endl;
	manager->setEntityName(player, "player_Eri");
	
	player = manager->getEntityByName("player_Eri");
	
	std::cout << "GameplayScene initialized!" << std::endl;


}



void GameplayScene::handleEvents(Event& event){

	
	giveEventsToFocus(event);

}

void GameplayScene::handleInput() {


   

}



void GameplayScene::render(Renderer* renderer){
	
	renderer->clear();
   	

	manager->draw();

}

void GameplayScene::update(float deltaTime){
	// handleInput();
	manager->update();	
}

void GameplayScene::clean(){
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->clean();
}
