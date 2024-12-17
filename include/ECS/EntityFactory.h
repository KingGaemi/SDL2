#pragma once
#include <memory>
#include <string>

class Entity;
class ECSManager; // 전방 선언
class AnimationData;

class EntityFactory {
public:
    std::shared_ptr<Entity> createBackgroundEntity(std::shared_ptr<ECSManager> ecsManager, const std::string& textureName);
    std::shared_ptr<Entity> createPlayerEntity(std::shared_ptr<ECSManager> ecsManager);
    int addAnimationFrames(AnimationData& animData, int x, int y, int w, int h, float duration, int interval, int count);
    // ... 필요한 팩토리 메서드를 추가

};