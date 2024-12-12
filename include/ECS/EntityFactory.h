#pragma once
#include <memory>
#include <string>

class Entity;
class ECSManager; // 전방 선언

class EntityFactory {
public:
    std::shared_ptr<Entity> createBackgroundEntity(std::shared_ptr<ECSManager> ecsManager, const std::string& textureName);
    std::shared_ptr<Entity> createPlayerEntity(std::shared_ptr<ECSManager> ecsManager);
    // ... 필요한 팩토리 메서드를 추가

};