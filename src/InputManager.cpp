#include "InputManager.h"
#include <SDL2/SDL.h>  // SDL 헤더는 cpp에서만 인클루드
#include <iostream>    // 필요하다면 디버그용

// SDL 키코드를 KeyCode로 변환하는 헬퍼 함수
static KeyCode translateSDLKey(SDL_Keycode sdlKey) {
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

void InputManager::pollEvents() {
    events.clear();
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        Event e;
        if (sdlEvent.type == SDL_QUIT) {
            if (quitCallback) {
                quitCallback();  // 콜백 호출
            }
        }
        if (sdlEvent.type == SDL_KEYDOWN) {
            e.type = "KEYDOWN";
            e.key = translateSDLKey(sdlEvent.key.keysym.sym);
            events.push_back(e);
        } else if (sdlEvent.type == SDL_KEYUP) {
            e.type = "KEYUP";
            e.key = translateSDLKey(sdlEvent.key.keysym.sym);
            events.push_back(e);
        }
        // 필요하다면 다른 이벤트(윈도우, 마우스 등)도 변환
    }
}

void InputManager::setQuitCallback(QuitCallback callback) {
    quitCallback = callback;
}

const std::vector<Event>& InputManager::getEvents() const {
    return events;
}
