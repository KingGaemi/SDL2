#pragma once
#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "Events/EventQueue.h"
#include "Events/EventManager.h"


class InputManager {
public:



    InputManager(EventManager* eventManager) : eventManager(eventManager) {}

    void handleEvents();

private:
    EventManager* eventManager;
    Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
    static KeyCode translateSDLKey(SDL_Keycode sdlKey);
    // 필요한 경우 private 헬퍼 함수들 추가 가능

};