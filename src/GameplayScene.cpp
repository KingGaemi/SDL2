#include "GameplayScene.h"
#include <iostream>




void GameplayScene::init(Renderer* renderer){

	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->load("eri", "res/gfx/eri_copy2.png", renderer);

}



void GameplayScene::handleEvents(Event& event){


}


void GameplayScene::render(Renderer* renderer){

	renderer->clear();

	// TextureManager* textureManager = TextureManager::getInstance();
	// SDL_Texture* bgTexture = textureManager->get("background_main");

	// if(bgTexture){
	// 	renderer->render(bgTexture, nullptr, nullptr);
	// }else{
	// 	// std::cerr << "bgTexture Failed" << std::endl;
	// }

	renderer->render()
	

}

void GameplayScene::update(float deltaTime){

}

void GameplayScene::clean(){
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->clean();
}
