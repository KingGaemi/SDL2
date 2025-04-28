#pragma once
#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "Requests.h"
#include "Components/Components.h"
#include "Manager/GameManager.h"

class Entity;
class ECSManager; // 전방 선언
class AnimationData;

using json = nlohmann::json;

class EntityFactory {
public:
    EntityFactory(std::shared_ptr<ECSManager>& ecsManager, std::shared_ptr<GameManager>& gameManager) : ecsManager(ecsManager) , gameManager(gameManager) {
        unitsJson = json::parse(std::ifstream("json/prefab/units_prefab.json"));
        objectsJson = json::parse(std::ifstream("json/prefab/objects_prefab.json"));
        uiJson = json::parse(std::ifstream("json/prefab/ui_prefab.json"));
        projectilesJson = json::parse(std::ifstream("json/prefab/projectiles_prefab.json"));
        itemsJson = json::parse(std::ifstream("json/prefab/items_prefab.json"));
        imagesJson = json::parse(std::ifstream("json/prefab/images_prefab.json"));
        registerComponentLoaders();
    }
    void configureEntity(const SpawnRequest& req, std::shared_ptr<Entity>& entity);
    void makeProps(const SpawnRequest& req);

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
    void loadUITag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadTextTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadIMGTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadHpBarTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadProjectileComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadDamageComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadItemComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadFloatingEffectComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadAbilityComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadAIComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadSpawnerComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadHitboxComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadHpBarComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadShadowComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadShakeEffectComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadSoundEffectComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadExplosionComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadClickableComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadTextLabelComponent(const json& componentData, std::shared_ptr<Entity> entity);
    void loadCoreTag(const json& componentData, std::shared_ptr<Entity> entity);
    void loadBossTag(const json& componentData, std::shared_ptr<Entity> entity);
    void applyRequests(std::shared_ptr<Entity> entity, const SpawnRequest& req);
    void registerComponentLoaders();
private:

    //Create information Json
    json unitsJson;
    json objectsJson;
    json uiJson;
    json projectilesJson;
    json itemsJson;
    json imagesJson;
    std::size_t nextItemID = 0;
    std::shared_ptr<ECSManager> ecsManager;
    std::shared_ptr<GameManager> gameManager;
    std::unordered_map<std::string, std::function<void(const json&, std::shared_ptr<Entity>)>> componentLoaders;
};