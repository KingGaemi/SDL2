#pragma once

#include <box2d/box2d.h>
#include <unordered_map>
#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Events/EventManager.h"


class ECSManager;




class PhysicsSystem : public System {



public:

	PhysicsSystem(std::shared_ptr<ECSManager>& ecsManager, std::shared_ptr<EventManager>& eventManager) : eventManager(eventManager),ecsManager(ecsManager) {
		init();
	}

    // 전역 또는 상수로

    // 변환 함수





    void init();
    void update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime) override;
    void destroyBody(std::shared_ptr<Entity> entity);
    void createBodies(std::vector<std::shared_ptr<Entity>>&entities);
    void setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities);
    void getContactEvents();
    void taskDestroyEvents();
    std::shared_ptr<Entity> shapeUserDataToEntity(b2ShapeId shapeId);
    void processDestroyQueue();
    void setInfoFromGame(std::vector<std::shared_ptr<Entity>>&entities);
    void applyMovementCommands(std::vector<std::shared_ptr<Entity>>&entities);
    void setBeforeStep(std::vector<std::shared_ptr<Entity>>&entities);

    std::shared_ptr<EventManager> eventManager;
private:
    int subStepCount = 8;
	b2WorldDef worldDef;
    b2WorldId worldId;
    std::shared_ptr<ECSManager> ecsManager;
    std::unordered_map<std::size_t, b2BodyId> bodyMap;
    std::queue<b2BodyId> destroyQueue;
};


