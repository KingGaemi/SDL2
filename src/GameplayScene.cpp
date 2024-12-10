#include "GameplayScene.h"
#include "Renderer.h"
#include <iostream>
#include <string>




void GameplayScene::init(Renderer* renderer){

	std::cout << "GameplayScene init : " << std::endl;
	std::string texureID = "eri_copy";
	TextureManager* textureManager = TextureManager::getInstance();	
	if(!textureManager->load(texureID, "res/gfx/eri_copy2.png", renderer)) {
	    std::cout << "Failed to load texture '"<< texureID <<"'" << std::endl;
	    return;
	}


	player = manager->createEntity();

	std::cout << "Player created" << std::endl;

	std::cout << "add TransfromComponent" << std::endl;
	playerTransform = &player->addComponent<TransformComponent>(10.0f, 10.0f);
	std::cout << "add TransfromComponent Complete" << std::endl;

		

    std::cout << "add SpriteComponent" << std::endl;
	player->addComponent<SpriteComponent>(texureID, playerTransform, renderer);
	std::cout << "setEntityName" << std::endl;
	manager->setEntityName(player, "player_Eri");
	
	player = manager->getEntityByName("player_Eri");
	
	std::cout << "GameplayScene initialized!" << std::endl;


}



void GameplayScene::handleEvents(Event& event){



}

void GameplayScene::handleInput() {


    // 초기화: 키 입력 없을 경우 속도를 0으로
    playerTransform->velocity.x = 0;
    playerTransform->velocity.y = 0;

    const Uint8* state = SDL_GetKeyboardState(NULL);

  // 대각선 입력 처리
    if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
        playerTransform->velocity.x = 1;
        playerTransform->velocity.y = -1;
    } else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
        playerTransform->velocity.x = -1;
        playerTransform->velocity.y = -1;
    } else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
        playerTransform->velocity.x = 1;
        playerTransform->velocity.y = 1;
    } else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
        playerTransform->velocity.x = -1;
        playerTransform->velocity.y = 1;
    } 
    // 단일 방향 입력 처리
    else {
        if (state[SDL_SCANCODE_RIGHT]) {
            playerTransform->velocity.x = 1;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            playerTransform->velocity.x = -1;
        }
        if (state[SDL_SCANCODE_UP]) {
            playerTransform->velocity.y = -1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            playerTransform->velocity.y = 1;
        }
    }




	if(state[SDL_SCANCODE_SPACE]){ std::cout << "FIRE " << std::endl; }

}



void GameplayScene::render(Renderer* renderer){
	
	renderer->clear();
   	

	manager->draw();

}

void GameplayScene::update(float deltaTime){
	handleInput();
	manager->update();	
}

void GameplayScene::clean(){
	TextureManager* textureManager = TextureManager::getInstance();
	textureManager->clean();
}
