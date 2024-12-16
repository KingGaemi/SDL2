#pragma once
#include <string>
#include <functional>
#include <memory>
#include "Events/EventQueue.h"

class ECSManager;
 // 게임 내부 이벤트(키 입력 등), SDL_Event 변환한 형태라 가정

class Scene {
public:
   

    Scene(const std::string& name, 
          std::shared_ptr<ECSManager> ecsManager)
        : name(name), ecsManager(ecsManager){}

    // virtual ~Scene() = default;

    // 씬이 활성화될 때 호출 (엔티티 생성, 시스템 등록 등)
    virtual void onEnter() = 0;

    // 씬이 비활성화될 때 호출 (엔티티 제거, 자원 정리 등)
    virtual void onExit() = 0;

    // 매 프레임 유저 입력 처리 (ECS Input System을 호출하거나 직접 처리 가능)
    virtual void handleEvents(const std::vector<Event>& events) = 0;

    // 매 프레임 게임 로직 업데이트 (deltaTime 단위)
    // 여기서 ecsManager->updateSystems(deltaTime)를 호출할 수도 있음.
    virtual void update(float deltaTime) = 0;

    // 매 프레임 렌더링
    // 여기서 씬이 직접 렌더러를 호출하지 않고, ecsManager가 가진 RenderSystem을 통해 렌더링
    // 혹은 RenderSystem을 ecsManager->getSystem<RenderSystem>() 형태로 얻어와 system->render() 호출
    virtual void render() = 0;

    std::string getName() const { return name; }

protected:
    std::string name;
    std::shared_ptr<ECSManager> ecsManager;
   	EventQueue sceneEventQueue;
};
