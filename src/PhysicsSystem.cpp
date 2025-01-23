#include "Systems/PhysicsSystem.h"
#include "Components/PositionComponent.h"
#include "Components/PhysicsComponent.h"
// #include "Components/ColliderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/ProjectileComponent.h"
#include "Groups.h"
#include "ECS/ECSManager.h"
#include <iostream>
// #include <math>



void PhysicsSystem::init() {

 	worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    // MyContactListener myListener;
    // world.SetContactListener(&myListener);
    worldId = b2CreateWorld(&worldDef);

}


void PhysicsSystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){

    createBodies(entities);
    int subStepCount = 8;
    b2World_Step(worldId, deltaTime, subStepCount);
    getContactEvents();
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

        if(!entity->isActive ||
            !entity->hasComponent<PhysicsComponent>() ||
            !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(physComp && !physComp->hasBody()){

            b2BodyDef bodyDef = b2DefaultBodyDef();
            bodyDef.userData = reinterpret_cast<void*>(static_cast<intptr_t>(entity->getID()));

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
            // auto colliderComp = entity->getComponent<ColliderComponent>();
            auto transComp = entity->getComponent<TransformComponent>();


            if(posComp){
                bodyDef.position = (b2Vec2){(posComp->x) / PIXELS_PER_METER,
                          (SCREEN_HEIGHT - posComp->y) / PIXELS_PER_METER};
                bodyDef.linearDamping = 10.0f;
                bodyDef.rotation.c = cos(angleToRadian(transComp->rotation));
                bodyDef.rotation.s = sin(angleToRadian(transComp->rotation));
                

                physComp->body = b2CreateBody(worldId, &bodyDef);
                b2Body_SetGravityScale(physComp->body, 0.0f);
                b2Polygon bodyBox;
                bodyBox = b2MakeBox((physComp->w) / PIXELS_PER_METER / 2.0,
                                    (physComp->h) / PIXELS_PER_METER / 2.0);
                b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
                bodyShapeDef.friction = 0.2f;
                bodyShapeDef.enableContactEvents = true;
                
                b2CreatePolygonShape(physComp->body, &bodyShapeDef, &bodyBox);
                b2Body_SetFixedRotation(physComp->body, true);
            }

            if(entity->hasComponent<ProjectileComponent>()){
                b2Body_SetFixedRotation(physComp->body, false);
            }
            // else
            // if(posComp && transComp){
            //     bodyDef.position = (b2Vec2){(posComp->x) / PIXELS_PER_METER,
            //               (SCREEN_HEIGHT - posComp->y) / PIXELS_PER_METER};
            //     physComp->body = b2CreateBody(worldId, &bodyDef);
            //     b2Polygon bodyBox;
            //     bodyBox = b2MakeBox(transComp->width * transComp->scale / PIXELS_PER_METER / 2.0,
            //                        transComp->height * transComp->scale  / PIXELS_PER_METER / 2.0);
            //     b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
            //     b2CreatePolygonShape(physComp->body, &bodyShapeDef, &bodyBox);
            // }

            // if(posComp && colliderComp && transComp) std::cout << colliderComp->collider.h << ", " << transComp->height << std::endl;
            ;
        }
    }
}



void PhysicsSystem::setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities){

    for(auto& entity: entities){

        if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(physComp->hasBody()){
            
            if (entity->hasComponent<VelocityComponent>()) {
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
            
            b2Vec2 pos = b2Body_GetPosition(physComp->body);
            b2Rot rot =  b2Body_GetRotation(physComp->body);
            float renderX = box2dToPixelX(pos.x) + physComp->offsetX;
            float renderY = box2dToPixelY(pos.y) + physComp->offsetY;
            
            // auto colliderComp = entity->getComponent<ColliderComponent>();
            // if(colliderComp){
            //     renderX += colliderComp->offsetX;
            //     renderY -= colliderComp->offsetY;
            // }


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

void PhysicsSystem::getContactEvents(){
    b2ContactEvents ce = b2World_GetContactEvents(worldId);
    // BeginTouch
    for (int i = 0; i < ce.beginCount; i++) {
        auto evt = ce.beginEvents + i;

        CollisionEvent collision;
        collision.type = CollisionType::Hit;
        collision.entityA = shapeUserDataToEntity(evt->shapeIdA);
        collision.entityB = shapeUserDataToEntity(evt->shapeIdB);
        ecsManager->collisionEvents.push_back(collision);       
        // shapeIdA, shapeIdB -> userData
        // push "CollisionBegin" event to ECS
    }

}

std::shared_ptr<Entity> PhysicsSystem::shapeUserDataToEntity(b2ShapeId shapeId){
    auto bodyId = b2Shape_GetBody(shapeId);
    auto udata = b2Body_GetUserData(bodyId);
    // std::cout << udata << std::endl;
    if (udata == 0) {
        return nullptr;
    }
    auto entityId =  reinterpret_cast<std::size_t>(udata);
    auto entity = ecsManager->getEntityById(entityId);
    return entity;
}