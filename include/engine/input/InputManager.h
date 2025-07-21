#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "Events/EventManager.h"


class InputManager {
public:
    InputManager(std::shared_ptr<EventManager>& eventManager) : eventManager(eventManager) {}
    void handleEvents();

private:
    std::shared_ptr<EventManager> eventManager;
    Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
    static KeyCode translateSDLKey(SDL_Keycode sdlKey);
    // 필요한 경우 private 헬퍼 함수들 추가 가능

};