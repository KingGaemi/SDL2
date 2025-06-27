#pragma once

#include "KeyCode.h"
#include <queue>
#include <optional>
#include <string>
// #include <mutex>

enum class EventType {
    QUIT,
    KEYDOWN,
    KEYUP,
    SCENE_CHANGE,
    CHARACTER_CHANGE,
    GAME_OVER,
    MOUSEMOTION,
    MOUSEBUTTONDOWN,
    MOUSEBUTTONUP,
	PAUSE,
	RESUME,
	GAMEOVER,
	WAVESTART,
    UNKNOWN
};

enum class AttackType{
    Attack,
    Cast,
    Shoot
};

struct SceneChangeEventData {
    std::string nextSceneName;
};

struct CharacterChangeEventDate{
    std::string characterName;
};

struct Event {
    EventType type;            // 이벤트 종류 (예: "KEYDOWN", "NETWORK")
    KeyCode key = KeyCode::Unknown;                     // 키 코드 (키보드 이벤트의 경우)
    std::optional<std::string>payload;         // 추가 데이터 (네트워크 메시지 등)
    std::optional<SceneChangeEventData> sceneChangeData;
    int mouseX, mouseY;
    bool mouseDown = false;
    bool clicked = false;
};

struct AttackEvent{
    std::size_t attackerId;
    std::size_t targetId;
    AttackType attackType;
    std::size_t abilityId;
    std::size_t abilityNumber;
};

struct DestroyEvent{
	std::size_t entityId;
	// etc...
};

struct KillEvent{
	std::size_t killerId;
	std::size_t victimId;
};

class EventManager {

public:
	void pushEvent(const Event& event){
		// std::lock_guard<std::mutex> lock(mtx);
		eventQueue.push(event);
	}
	void pushMiddleEvent(const Event& event){
		middleEventQueue.push(event);
	}
	void pushBigEvent(const Event& event){
		bigEventQueue.push(event);
	}
	void pushAttackEvent(const AttackEvent& event){
		attackEvents.push(event);
	}
	void pushDestroyEvent(const DestroyEvent& event){
		destroyEvents.push_back(event);
	}
	void pushKillEvent(const KillEvent& event){
		killEvents.push(event);
	}
	bool pollEvent(Event& outEvent) {
		// std::lock_guard<std::mutex> lock(mtx);
		if(eventQueue.empty()) return false;
		outEvent = eventQueue.front();
		eventQueue.pop();
		return true;
	}
	bool pollMiddleEvent(Event& outEvent){
		if(middleEventQueue.empty()) return false;
		outEvent = middleEventQueue.front();
		middleEventQueue.pop();
		return true;
	}
	bool pollBigEvent(Event& outEvent) {
		if(bigEventQueue.empty()) return false;
		outEvent = bigEventQueue.front();
		bigEventQueue.pop();
		return true;
	}
	bool pollAttackEvent(AttackEvent& outEvent){
		if(attackEvents.empty()) return false;
		outEvent = attackEvents.front();
		attackEvents.pop();
		return true;
	}
	bool pollKillEvent(KillEvent& outEvent){
		if(killEvents.empty()) return false;
		outEvent = killEvents.front();
		killEvents.pop();
		return true;
	}
    const std::vector<DestroyEvent>& getDestroyEvents() const {
        return destroyEvents;
    }

    void clearDestroyEvents() {
        destroyEvents.clear();
    }

	EventManager* get(){
		return this;
	}


private:
	std::queue<Event> eventQueue;
	std::queue<Event> bigEventQueue;
	std::queue<Event> middleEventQueue;
	std::queue<AttackEvent> attackEvents;
	std::queue<KillEvent> killEvents;
	std::vector<DestroyEvent> destroyEvents;
	// std::mutex mtx;
};