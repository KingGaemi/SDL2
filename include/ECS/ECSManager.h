// ECSManager.h
#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "EntityFactory.h"
#include "Systems/PhysicsSystem.h"
#include "Groups.h"
#include "Entity.h"
#include "System.h"


enum class SystemGroup {
    Logic,
    Render,
    UI,
    Event
};

enum class CollisionType {
    Crash,
    Hit
};


struct SystemRegistration {
    std::shared_ptr<System> system;
    SystemGroup group;
    int priority; // 그룹 내 우선순위
};

struct CollisionEvent {
    CollisionType type;
    std::shared_ptr<Entity> entityA;
    std::shared_ptr<Entity> entityB;
};


class ECSManager {
public:




    std::shared_ptr<Entity> createEntity();
    void destroyEntity(std::shared_ptr<Entity> entity);

    // 엔티티 접근
    std::shared_ptr<Entity> getEntityById(std::size_t id);
    void setEntityName(std::shared_ptr<Entity> entity, const std::string& name);
    std::shared_ptr<Entity> getEntityByName(const std::string& name);

    // 시스템 추가/업데이트
    template<typename S, typename... Args>
    void addSystem(SystemGroup group, int priority ,Args&&... args) {
        // SystemTypeID typeID = getSystemTypeID<S>();
        // if (systemBitset[typeID]) {
        //     throw std::runtime_error("System already exists on this ECSManager!");
        // }
        auto system = std::make_shared<S>(std::forward<Args>(args)...);
        SystemRegistration reg;
        reg.system   = system;
        reg.group    = group;
        reg.priority = priority;
        registeredSystems.push_back(reg);

        // systemArray[typeID] = system;
        // systemBitset[typeID] = true;
    }
    void updateSystems(float deltaTime);
    void renderSystems(float deltaTime);

    template<typename S>
    std::shared_ptr<S> getSystem(){
        for (auto& reg : registeredSystems) {
            auto casted = std::dynamic_pointer_cast<S>(reg.system);
            if (casted) {
                return casted;
            }
        }
        return nullptr;
    }

    template<typename S>
    void removeSystem() {
        registeredSystems.erase(
            std::remove_if(registeredSystems.begin(), registeredSystems.end(),
                [](auto& reg){
                    return (std::dynamic_pointer_cast<S>(reg.system) != nullptr);
                }),
            registeredSystems.end()
        );
    }



    // Temporary
    void takeSingleRequest(const SpawnRequest& req);


    std::vector<CollisionEvent>& getCollisionEvents() {
        return collisionEvents;
    }

    std::shared_ptr<EntityFactory> shareFactory();

    void setFactory(std::shared_ptr<EntityFactory>& factory);
    void setPhysicsSystem(std::shared_ptr<PhysicsSystem>& physSystem);
    void setVelocity(std::shared_ptr<Entity> entity, float x, float y);
    void processSpawnRequests();
    void processCollisionEvents();
    void processMiddleEvents();

    void cleanUpEntities();
    void cleanUpAllEntities();
    void cleanUpEntitiesByScene(SceneCode sceneCode);
    // 엔티티 이름 관리 (선택 사항)

    std::vector<SpawnRequest> pendingSpawns;
    std::vector<CollisionEvent> collisionEvents;
private:
    std::size_t nextID = 0;
    std::vector<std::shared_ptr<Entity>> entities;


    // 이름 관리 (원한다면 유지)
    std::unordered_map<std::string, std::shared_ptr<Entity>> entityByName;
    std::unordered_map<std::shared_ptr<Entity>, std::string> entityNames;

    std::shared_ptr<EntityFactory> entityFactory;

    std::shared_ptr<PhysicsSystem> physicsSystem;
    // SystemArray systemArray{};
    // SystemBitset systemBitset;
    std::vector<SystemRegistration> registeredSystems;
};
