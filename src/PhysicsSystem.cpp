#include "Systems/PhysicsSystem.h"
#include "Components/PositionComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/Transformcomponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PlayableComponent.h"
#include "Groups.h"
#include <iostream>



void PhysicsSystem::init() {

 	worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);

}


void PhysicsSystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){

    createBodies(entities);

    int subStepCount = 8;
    b2World_Step(worldId, deltaTime, subStepCount);

    setPositionsFromWorld(entities);
}



void PhysicsSystem::destroyBody(std::shared_ptr<Entity> entity) {
    if (!entity->hasComponent<PhysicsComponent>()) return;

    auto physComp = entity->getComponent<PhysicsComponent>();
    
    if (physComp->hasBody()) {
        b2DestroyBody(physComp->body);
        physComp->body = b2_nullBodyId;
    }
}

void PhysicsSystem::createBodies(std::vector<std::shared_ptr<Entity>>&entities){
    for(auto& entity: entities){

        if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(!physComp->hasBody()){

            b2BodyDef bodyDef = b2DefaultBodyDef();

            if(physComp->bodyType == BodyType::Kinematic){
                bodyDef.type = b2_kinematicBody;
            }else if(physComp->bodyType == BodyType::Static){
                bodyDef.type = b2_staticBody;
            }else if(physComp->bodyType == BodyType::Dynamic){
                bodyDef.type = b2_dynamicBody;
            }else{
                bodyDef.type = b2_dynamicBody;
            }

            auto posComp = entity->getComponent<PositionComponent>();
            
            if(posComp){
                bodyDef.position = (b2Vec2){posComp->x / PIXELS_PER_METER, (SCREEN_HEIGHT - posComp->y) / PIXELS_PER_METER };
            }

            physComp->body = b2CreateBody(worldId, &bodyDef);

            b2Polygon bodyBox;
            auto transComp = entity->getComponent<TransformComponent>();
            if(transComp){
                bodyBox = b2MakeBox(transComp->width / PIXELS_PER_METER, transComp->height / PIXELS_PER_METER);
            }
            b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
            b2CreatePolygonShape(physComp->body, &bodyShapeDef, &bodyBox);
     
        }
    }
}



void PhysicsSystem::setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities){

    for(auto& entity: entities){

            if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

            auto physComp = entity->getComponent<PhysicsComponent>();

            if(physComp->hasBody()){
                if(entity->hasComponent<PlayerTag>() || entity->hasComponent<Player2Tag>()){
                    
                    b2Body_SetFixedRotation(physComp->body, true);
                    b2Body_SetGravityScale(physComp->body, 0.0f );

                    if (entity->hasComponent<VelocityComponent>() && entity->hasComponent<PlayableComponent>()) {
                        // velocityComponent 등에서 얻은 vx, vy
                        auto veloComp = entity->getComponent<VelocityComponent>();

                        // 픽셀→미터 변환
                        float vx = veloComp->x() / PIXELS_PER_METER; // pixel/sec or so
                        float vy = -veloComp->y() / PIXELS_PER_METER;

                        b2Vec2 vel;
                        vel.x = vx;
                        vel.y = vy;

                        b2Body_SetLinearVelocity(physComp->body, vel);
                        
                    }

                }

                
                b2Vec2 pos = b2Body_GetPosition(physComp->body);
                b2Rot rot =  b2Body_GetRotation(physComp->body);
                float renderX = box2dToPixelX(pos.x);
                float renderY = box2dToPixelY(pos.y);
                       
                auto posComp = entity->getComponent<PositionComponent>();
                if(posComp){
                    posComp->set(renderX, renderY);
                }

                if(entity->hasComponent<TransformComponent>()){
                    auto transComp = entity->getComponent<TransformComponent>();

                    if(transComp){
                        float degAngle = box2dToPixelAngle(b2Rot_GetAngle(rot));
                        transComp->rotation = -degAngle; 
                    }
                }
            }
        }

}