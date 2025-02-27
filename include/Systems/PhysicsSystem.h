#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Events/EventManager.h"
#include "ECS/ECSManager.h"
#include "MapManager.h"




class PhysicsSystem : public System {



public:

	PhysicsSystem(std::shared_ptr<ECSManager>& ecsManager, std::shared_ptr<EventManager>& eventManager, std::shared_ptr<MapManager> mapManager) : eventManager(eventManager) , mapManager(mapManager), ecsManager(ecsManager){
		init();
	}

    // 전역 또는 상수로

    // 변환 함수

    void init();
    void update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime) override;
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

    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<MapManager> mapManager;
private:
    int subStepCount = 8;
	b2WorldDef worldDef;
    b2WorldId worldId;
    std::shared_ptr<ECSManager> ecsManager;
    std::unordered_map<std::size_t, b2BodyId> bodyMap;
    std::vector<b2BodyId> walls;
    std::queue<b2BodyId> destroyQueue;
};


