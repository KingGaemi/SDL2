#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "engine/ecs/core/EntityManager.h"
#include "engine/ecs/core/ComponentManager.h"
#include "engine/event/EventManager.h"
#include "engine/ecs/core/System.h"
#include "game/map/MapManager.h"


class PhysicsSystem : public System {



public:

	PhysicsSystem(std::shared_ptr<EntityManager> em,
                  std::shared_ptr<ComponentManager> cm,
                  std::shared_ptr<EventManager> ev, 
                  std::shared_ptr<MapManager> mm)
        : entityMgr(em), compMgr(cm), eventMgr(ev), mapMgr(mm){
		init();
	}

    // 전역 또는 상수로

    // 변환 함수

    void init();
    void update(float deltaTime) override;
    void destroyBody(std::shared_ptr<Entity> entity);
    void cleanUpDeadBodies(std::vector<std::shared_ptr<Entity>>& entities);
    void createBodies(std::vector<std::shared_ptr<Entity>>&entities);
    void setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities);
    void getContactEvents();
    void taskDestroyEvents();
    std::shared_ptr<Entity> shapeUserDataToEntity(b2ShapeId shapeId);
    void processDestroyQueue();
    void setInfoFromGame(std::vector<std::shared_ptr<Entity>>&entities);
    void applyMovementCommands(std::vector<std::shared_ptr<Entity>>&entities);
    void setBeforeStep(std::vector<std::shared_ptr<Entity>>&entities);
    void createWalls();

 
private:
    int subStepCount = 8;
	b2WorldDef worldDef;
    b2WorldId worldId;
    std::shared_ptr<EntityManager> entityMgr;
    std::shared_ptr<ComponentManager> compMgr;
    std::shared_ptr<EventManager> eventMgr;
    std::shared_ptr<MapManager> mapMgr;
    std::unordered_map<std::size_t, b2BodyId> bodyMap;
    std::vector<b2BodyId> walls;
    std::queue<b2BodyId> destroyQueue;
};


