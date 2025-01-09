#pragma once
#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "Requests.h"
#include "Components/Components.h"

class Entity;
class ECSManager; // 전방 선언
class AnimationData;

using json = nlohmann::json;

class EntityFactory {
public:
    EntityFactory(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager) {
        unitsJson = json::parse(std::ifstream("createInfo/units.json"));
        objectsJson = json::parse(std::ifstream("createInfo/objects.json"));
        uiJson = json::parse(std::ifstream("createInfo/ui.json"));
        projectilesJson = json::parse(std::ifstream("createInfo/projectiles.json"));
        registerComponentLoaders();
    }
    void createEntity(const SpawnRequest& req);

    void loadPositionComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadPhysicsComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadSpriteComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadAnimationComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadSceneTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadTeamTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadDirectionComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadVelocityComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadTransformComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadColliderComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadStateComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadStatusComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadCommandComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadMovementCommandComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadPlayableComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadCooldownComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadDashComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadPlayerTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadProjectileComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadDamageComponent(const json& componentData, std::shared_ptr<Entity> entity);

    void applyRequests(std::shared_ptr<Entity> entity, const SpawnRequest& req);
    void registerComponentLoaders();
private:

    //Create information Json
    json unitsJson;
    json objectsJson;
    json uiJson;
    json projectilesJson;

    std::shared_ptr<ECSManager> ecsManager;
    std::unordered_map<std::string, std::function<void(const json&, std::shared_ptr<Entity>)>> componentLoaders;
};