#include "MenuScene.h"
#include "GameplayScene.h"
#include "Renderer.h"
#include <iostream>




void MenuScene::init(Renderer* renderer){

	if (this->manager) {
        std::cout << "MenuScene initialized with a valid manager." << std::endl;
    } else {
        std::cerr << "MenuScene initialized with a nullptr manager!" << std::endl;
    }
	
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->load("background_main", "res/gfx/SunnyLand/Environment/back.png", renderer);
	
	renderer->clear();
	
	renderer->draw("background_main", nullptr, nullptr);
	
	renderer->display();
}



void MenuScene::handleEvents(Event& event){
	if(event.type == "KEYDOWN" && event.key == SDLK_RETURN){

		std::cout << "Enter Pressed! " << std::endl;
		auto newScene = std::make_shared<GameplayScene>(
            [this](const std::shared_ptr<Scene>& scene) {
                changeSceneCallback(scene);
            },
            manager
        );
		std::cout << "Callback === " << std::endl;
		changeSceneCallback(newScene);
		std::cout << "changeSceneCallback ^^^ " << std::endl;
	}

}


void MenuScene::render(Renderer* renderer){

	


	
	
	

}

void MenuScene::update(float deltaTime){

}

void MenuScene::clean(){
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->clean();
}
