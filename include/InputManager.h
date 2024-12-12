#pragma once
#include <functional>
#include <vector>
#include "EventQueue.h"



class InputManager {
public:
    using QuitCallback = std::function<void()>;
    // 이벤트를 업데이트(폴링)하는 함수, 매 프레임 호출.
    void pollEvents();
    // 현재 프레임 수집한 이벤트 리스트 반환
    const std::vector<Event>& getEvents() const;

    void setQuitCallback(QuitCallback callback);
private:
    std::vector<Event> events;
    QuitCallback quitCallback;

    // 필요한 경우 private 헬퍼 함수들 추가 가능
};