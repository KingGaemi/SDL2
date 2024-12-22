// ECSManager.h
#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "EntityFactory.h"
#include "Entity.h"
#include "System.h"


using SystemBitset = std::bitset<MAX_SYSTEMS>;
using SystemArray = std::array<std::shared_ptr<System>, MAX_SYSTEMS>;

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
    void addSystem(Args&&... args) {
        SystemTypeID typeID = getSystemTypeID<S>();
        if (systemBitset[typeID]) {
            throw std::runtime_error("System already exists on this ECSManager!");
        }
        auto system = std::make_shared<S>(std::forward<Args>(args)...);
        systemArray[typeID] = system;
        systemBitset[typeID] = true;
    }
    void updateSystems(float deltaTime);

    template<typename S>
    std::shared_ptr<S> getSystem() const {
        SystemTypeID typeID = getSystemTypeID<S>();
        if (!systemBitset[typeID]) return nullptr;
        return std::static_pointer_cast<S>(systemArray[typeID]);
    }

    template<typename S>
    void removeSystem() {
        SystemTypeID typeID = getSystemTypeID<S>();
        if (systemBitset[typeID]) {
            systemBitset[typeID] = false;
            systemArray[typeID].reset();
        }
    }



    // Temporary
    void takeSingleRequest(const SpawnRequest& req);



    std::shared_ptr<EntityFactory> shareFactory();
    void setFactory(std::shared_ptr<EntityFactory>& factory);
    void setVelocity(std::shared_ptr<Entity> entity, float x, float y);
    void processSpawnRequests();
    void cleanUpEntities();
    // 엔티티 이름 관리 (선택 사항)

    std::vector<SpawnRequest> pendingSpawns;
private:
    std::size_t nextID = 0;
    std::vector<std::shared_ptr<Entity>> entities;


    // 이름 관리 (원한다면 유지)
    std::unordered_map<std::string, std::shared_ptr<Entity>> entityByName;
    std::unordered_map<std::shared_ptr<Entity>, std::string> entityNames;

    std::shared_ptr<EntityFactory> entityFactory;


    SystemArray systemArray{};
    SystemBitset systemBitset;
};
