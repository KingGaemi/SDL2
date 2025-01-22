#pragma once

#include <box2d/box2d.h>
#include "ECS/Entity.h"
#include "ECS/System.h"

class ECSManager;




class PhysicsSystem : public System {



public:

	PhysicsSystem(std::shared_ptr<ECSManager>& ecsManager) : ecsManager(ecsManager){
		init();
	}

    // 전역 또는 상수로
    const float PIXELS_PER_METER = 50.0f; // 예: 30px = 1m
    const float SCREEN_HEIGHT = 800.0f;

    // 변환 함수
    inline float box2dToPixelX(float x) { return x * PIXELS_PER_METER; }
    inline float box2dToPixelY(float y) { return -y * PIXELS_PER_METER + SCREEN_HEIGHT; }

    inline float box2dToPixelAngle(float angle) {
    // 라디안 -> 도 or 그냥 라디안 그대로 SDL_RenderCopyEx에 전달
        return angle * (180.0f / 3.14159f);
    }
    inline float angleToRadian(float angle) {
    // 라디안 -> 도 or 그냥 라디안 그대로 SDL_RenderCopyEx에 전달
        return angle * (3.14159f / 180.0f); 
    }



    void init();
    void update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime) override;
    void destroyBody(std::shared_ptr<Entity> entity);
    void createBodies(std::vector<std::shared_ptr<Entity>>&entities);
    void setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities);
    void getContactEvents();
    std::shared_ptr<Entity> shapeUserDataToEntity(b2ShapeId shapeId);

private:
	b2WorldDef worldDef;
    b2WorldId worldId;
    std::shared_ptr<ECSManager> ecsManager;

};


