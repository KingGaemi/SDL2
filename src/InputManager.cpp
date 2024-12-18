#include "Input/InputManager.h"
#include <iostream>    // 필요하다면 디버그용




void InputManager::handleEvents(){
    SDL_Event sdlEvent;
    
    while (SDL_PollEvent(&sdlEvent)){
        Event gameEvent = convertSDLEventToGameEvent(sdlEvent);
        if (gameEvent.type == EventType::QUIT) {
            eventManager->pushBigEvent(gameEvent);
        }
        if(gameEvent.type == EventType::KEYDOWN) {
            eventManager->pushEvent(gameEvent);
        }
        if(gameEvent.type == EventType::KEYUP) {
            eventManager->pushEvent(gameEvent);
        }
        if(gameEvent.type == EventType::UNKNOWN){
            // std::cout << "EventType : UNKNOWN " << std::endl;  
        }
    }
}



Event InputManager::convertSDLEventToGameEvent(const SDL_Event& sdlEvent) {
            Event gameEvent;

            switch (sdlEvent.type) {
            case SDL_QUIT:
                gameEvent.type = EventType::QUIT;
                break;
            case SDL_KEYDOWN:
                gameEvent.type = EventType::KEYDOWN;
                gameEvent.key = translateSDLKey(sdlEvent.key.keysym.sym);
                break;
            case SDL_KEYUP:
                gameEvent.type = EventType::KEYUP;
                gameEvent.key = translateSDLKey(sdlEvent.key.keysym.sym);
                break;
            default:
                // std::cout << "Unhandled SDL Event type: " << sdlEvent.type << std::endl;
                // if (sdlEvent.type == SDL_WINDOWEVENT) {
                //     std::cout << "SDL_WINDOWEVENT: " << (int)sdlEvent.window.event << std::endl;
                // }
                gameEvent.type = EventType::UNKNOWN;
                break;
            }

            return gameEvent;
}

// SDL 키코드를 KeyCode로 변환하는 헬퍼 함수
KeyCode InputManager::translateSDLKey(SDL_Keycode sdlKey) {
    switch (sdlKey) {
        case SDLK_RETURN: return KeyCode::Enter;
        case SDLK_ESCAPE: return KeyCode::Escape;
        case SDLK_LEFT:   return KeyCode::Left;
        case SDLK_RIGHT:  return KeyCode::Right;
        case SDLK_UP:     return KeyCode::Up;
        case SDLK_DOWN:   return KeyCode::Down;
        default:          return KeyCode::Unknown;
    }
}
