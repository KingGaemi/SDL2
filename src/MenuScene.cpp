#include "MenuScene.h"
#include <iostream>




void MenuScene::init(Renderer* renderer){

	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->load("background_main", "res/gfx/SunnyLand/Environment/back.png", renderer);

}



void MenuScene::handleEvents(Event& event){
	if(event.type == "KEYDOWN" && event.key == SDLK_RETURN){

		std::cout << "Enter Pressed! " << std::endl;
		changeSceneCallback("GameplayScene");
		
	}

}


void MenuScene::render(Renderer* renderer){

	renderer->clear();

	TextureManager* textureManager = TextureManager::getInstance();
	SDL_Texture* bgTexture = textureManager->get("background_main");

	if(bgTexture){
		renderer->render(bgTexture, nullptr, nullptr);
	}else{
		// std::cerr << "bgTexture Failed" << std::endl;
	}

	

}

void MenuScene::update(float deltaTime){

}

void MenuScene::clean(){
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->clean();
}
