#pragma once
#include <memory>
#include <string>
#include "Requests.h"

class Entity;
class ECSManager; // 전방 선언
class AnimationData;

class EntityFactory {
public:


    EntityFactory(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {}


    void createBackgroundEntity(const std::string& textureName);
    void createPlayerEntity(const SpawnRequest& req);
    void createFarmerEntity(const SpawnRequest& req);
    void createSlashEntity(const AttackRequest& req);
    // void createAttack(std::shared_ptr<ECSManager> ecsManager, float x, float y);
    int addAnimationFrames(AnimationData& animData, int x, int y, int w, int h, float duration, int interval, int count);
    // ... 필요한 팩토리 메서드를 추가

private:

    std::shared_ptr<ECSManager> ecsManager;

};