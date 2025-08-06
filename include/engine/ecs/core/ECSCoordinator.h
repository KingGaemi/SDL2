#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "engine/ecs/core/EntityManager.h"
#include "engine/ecs/core/ComponentManager.h"
#include "engine/ecs/core/SystemManager.h"
#include "engine/event/EventManager.h"
#include "engine/factory/EntityFactory.h"

class ECSCoordinator {
public:
    ECSCoordinator(
      std::shared_ptr<EntityManager>    em,
      std::shared_ptr<ComponentManager> cm,
      std::shared_ptr<SystemManager>    sm,
      std::shared_ptr<EntityFactory>    ef,
      std::shared_ptr<EventManager>     ev
    )
    : entityMgr(std::move(em))
    , compMgr(std::move(cm))
    , sysMgr(std::move(sm))
    , factory(std::move(ef))
    , eventMgr(std::move(ev))
    {}

    std::shared_ptr<Entity> createEntity(){
        return entityMgr->create();
    }

    void destroyEntity(EntityID eid){
        entityMgr->destroy(entityMgr->getById(eid));        
    }

    template<typename C, typename... Args>
    void addComponent(EntityID id, Args&&... args) {
        compMgr->addComponent<C>(id, std::forward<Args>(args)...);
    }

    template<typename C>
    std::shared_ptr<C> getComponent(EntityID id) {
        return compMgr->getComponent<C>(id);
    }

    template<typename S, typename... Args>
    void addSystem(SystemGroup g, int prio, Args&&... a) {
        sysMgr->addSystem<S>(g, prio, std::forward<Args>(a)...);
    }
    void update(float dt) {
        sysMgr->update(dt);
    }

    void pushEvent(const Event& e) {
      eventMgr->pushEvent(e);
    }

    void updateSystems(float deltaTime);
    void renderSystems(float deltaTime);
    void renderUI(float deltaTime);

    // Temporary
    void takeSingleRequest(const SpawnRequest& req);

    std::shared_ptr<EntityFactory> shareFactory();

    void setFactory(std::shared_ptr<EntityFactory>& factory);
   
    void processSpawnRequests();
    void processCollisionEvents();
    void processMiddleEvents();
    void processTerminatedEntities();
    void cleanUpEntities();
    void cleanUpAllEntities();
    void activeMapEntity();
    void makeCamera();

    std::shared_ptr<Entity> getCamera();
    // 엔티티 이름 관리 (선택 사항)

    std::vector<SpawnRequest> pendingSpawns;
    std::vector<ProjectileRequest> pendingProjectiles;
    // std::vector<CollisionEvent> collisionEvents;

private:
    std::shared_ptr<EntityManager>    entityMgr;
    std::shared_ptr<ComponentManager> compMgr;
    std::shared_ptr<SystemManager>    sysMgr;
    std::shared_ptr<EntityFactory>    factory;
    std::shared_ptr<EventManager>     eventMgr;
    // std::shared_ptr<Entity> mapEntity;
    // 이름 관리 (원한다면 유지)

    bool activeMap = false;
};
