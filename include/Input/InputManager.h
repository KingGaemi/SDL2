#pragma once
#include <functional>
#include <vector>
#include <SDL2/SDL.h>
#include "Events/EventQueue.h"
#include "Events/EventManager.h"


class InputManager {
public:

    // 이벤트를 업데이트(폴링)하는 함수, 매 프레임 호출.
    using QuitCallback = std::function<void()>;

    InputManager(EventManager* eventManager) : eventManager(eventManager) {}

    void handleEvents();

    void setQuitCallback(QuitCallback callback);
private:
    EventManager* eventManager;
    QuitCallback quitCallback;
    Event convertSDLEventToGameEvent(const SDL_Event& sdlEvent);
    static KeyCode translateSDLKey(SDL_Keycode sdlKey);
    // 필요한 경우 private 헬퍼 함수들 추가 가능
    
};