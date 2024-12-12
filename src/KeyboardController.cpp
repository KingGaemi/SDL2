#include "Components/KeyboardController.h"
#include <iostream>





KeyboardController::KeyboardController(std::shared_ptr<TransformComponent> p_transform){
	
	transform = p_transform;
	// init();

}



void KeyboardController::update(){


	// 초기화: 키 입력 없을 경우 속도를 0으로
    transform->velocity.x = 0;
    transform->velocity.y = 0;

    const Uint8* state = SDL_GetKeyboardState(NULL);

  // 대각선 입력 처리
    if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
        transform->velocity.x = 1;
        transform->velocity.y = -1;
    } else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
        transform->velocity.x = -1;
        transform->velocity.y = -1;
    } else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
        transform->velocity.x = 1;
        transform->velocity.y = 1;
    } else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
        transform->velocity.x = -1;
        transform->velocity.y = 1;
        std::cout << "DOWN" << std::endl;
    } 
    // 단일 방향 입력 처리
    else {
        if (state[SDL_SCANCODE_RIGHT]) {
            transform->velocity.x = 1;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            transform->velocity.x = -1;
        }
        if (state[SDL_SCANCODE_UP]) {
            transform->velocity.y = -1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            transform->velocity.y = 1;
        }
    }







}