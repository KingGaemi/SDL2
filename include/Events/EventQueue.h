#pragma once
#include <queue>
#include <functional>
#include <string>
#include <optional>
#include "KeyCode.h"


enum class EventType {
    QUIT,
    KEYDOWN,
    KEYUP,
    SCENE_CHANGE,
    GAME_OVER,
    UNKNOWN
};



struct SceneChangeEventData {
    std::string nextSceneName;
};


struct Event {
    EventType type;            // 이벤트 종류 (예: "KEYDOWN", "NETWORK")
    KeyCode key = KeyCode::Unknown;                     // 키 코드 (키보드 이벤트의 경우)
    std::optional<std::string>payload;         // 추가 데이터 (네트워크 메시지 등)
    std::optional<SceneChangeEventData> sceneChangeData;
};



class EventQueue{

public:
    void push(const Event& event);
    Event pop();
    bool isEmpty() const;

private:
    std::queue<Event> events;



};