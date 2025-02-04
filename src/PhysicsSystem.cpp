#include "Systems/PhysicsSystem.h"
#include "Components/PositionComponent.h"
#include "Components/PhysicsComponent.h"
// #include "Components/ColliderComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/HitboxComponent.h"
#include "Groups.h"
#include "ECS/ECSManager.h"
#include "myMath.h"
#include <iostream>


// #include <math>



void PhysicsSystem::init() {

 	worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);

}


void PhysicsSystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){
    createBodies(entities);
    setBeforeStep(entities);
    b2World_Step(worldId, deltaTime, subStepCount);
    getContactEvents();
    taskDestroyEvents();
    processDestroyQueue();
    setPositionsFromWorld(entities);
}

void PhysicsSystem::destroyBody(std::shared_ptr<Entity> entity) {
    if (!entity->hasComponent<PhysicsComponent>()) return;
    auto physComp = entity->getComponent<PhysicsComponent>();
    
    if (physComp->hasBody()) {
        // 맵에서 제거
        auto it = bodyMap.find(entity->getId());
        if (it != bodyMap.end()) {
            bodyMap.erase(it);
        }
        destroyQueue.push(physComp->body); 
        physComp->body = b2_nullBodyId;
    }
}

void PhysicsSystem::createBodies(std::vector<std::shared_ptr<Entity>>&entities){
    for(auto& entity: entities){

        if(!entity->isActive ||
            !entity->hasComponent<PhysicsComponent>() ||
            !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(!physComp->hasBody()){

            b2BodyDef bodyDef = b2DefaultBodyDef();
            bodyDef.userData = reinterpret_cast<void*>(static_cast<intptr_t>(entity->getId()));

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
            bodyDef.position = (b2Vec2){(posComp->x) / PIXELS_PER_METER,
                      (SCREEN_HEIGHT - posComp->y) / PIXELS_PER_METER};

            auto transComp = entity->getComponent<TransformComponent>();
            // (1) TransformComponent->rotation : 0°=오른쪽
            // (2) toRadian() : 도→라디안, 0도 -> 0라디안
            if (transComp) {
                float rad = toRadian(transComp->rotation); // 0=오른쪽
                bodyDef.rotation.c = cos(rad);
                bodyDef.rotation.s = sin(rad);
            }

            bodyDef.linearDamping = 10.0f;

            physComp->body = b2CreateBody(worldId, &bodyDef);               
            bodyMap.emplace(entity->getId(), physComp->body);
            b2Body_SetGravityScale(physComp->body, 0.0f);
            
            if(physComp->w != 0 && physComp->h != 0){
                b2Polygon bodyBox;
                bodyBox = b2MakeBox((physComp->w) / PIXELS_PER_METER / 2.0,
                                    (physComp->h) / PIXELS_PER_METER / 2.0);
                b2ShapeDef bodyShapeDef = b2DefaultShapeDef();
                bodyShapeDef.friction = 0.2f;
                b2CreatePolygonShape(physComp->body, &bodyShapeDef, &bodyBox);
            }

            if(entity->hasComponent<HitboxComponent>()){
                auto hitboxComp = entity->getComponent<HitboxComponent>();
                b2Polygon hitbox;
                hitbox = b2MakeBox((hitboxComp->w) / PIXELS_PER_METER / 2.0,
                                (hitboxComp->h) / PIXELS_PER_METER / 2.0);
                b2ShapeDef hitboxShapeDef = b2DefaultShapeDef();
                if(entity->hasComponent<ProjectileComponent>()){
                    b2Body_SetFixedRotation(physComp->body, false);
                }else{
                    b2Body_SetFixedRotation(physComp->body, true);
                }
                // hitboxShapeDef.enableSensorEvents = true;
                // hitboxShapeDef.isSensor = true;
                b2CreatePolygonShape(physComp->body, &hitboxShapeDef, &hitbox);
            }
        }
    }
}


void PhysicsSystem::setBeforeStep(std::vector<std::shared_ptr<Entity>>&entities){
    std::vector<std::shared_ptr<Entity>> physicsEntity = setInfoFromGame(entities);
    applyMovementCommands(physicsEntity);

    // etc..
}



std::vector<std::shared_ptr<Entity>> PhysicsSystem::setInfoFromGame(std::vector<std::shared_ptr<Entity>>&entities){

    std::vector<std::shared_ptr<Entity>> physicsEntity;

    for(auto& entity: entities){

        if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(physComp->hasBody()){
            
            if (entity->hasComponent<VelocityComponent>()) {
                // velocityComponent 등에서 얻은 vx, vy
                auto veloComp = entity->getComponent<VelocityComponent>();

                // 픽셀→미터 변환
                float vx = veloComp->x() / PIXELS_PER_METER; // pixel/sec or so
                float vy = -veloComp->y() / PIXELS_PER_METER; // sdl2와 box2의 y 방향은 반대
                
                b2Vec2 vel;
                vel.x = vx;
                vel.y = vy;

                b2Body_SetLinearVelocity(physComp->body, vel);                
            }
            if (entity->hasComponent<TransformComponent>() && entity->hasComponent<PositionComponent>()) {
                // TransformComponent에서 위치와 회전값 가져오기
                auto transComp = entity->getComponent<TransformComponent>();
                auto posComp = entity->getComponent<PositionComponent>();
                // 픽셀 → 미터 변환
                // 각도(degree) → 라디안 변환
                // float rotation = transComp->rotation * (3.14 / 180.0f);


                // Box2D Transform 적용 
                // position 포함
                // b2Vec2 pos = {posComp->x, posComp->y};
                // if(entity->hasComponent<PlayerTag>()) std::cout << posComp->x << ","<< posComp->y << std::endl;
                b2Body_SetTransform(physComp->body, b2Body_GetPosition(physComp->body), b2MakeRot(toRadian(transComp->rotation)));
                
            }



            physicsEntity.push_back(entity);
        }
    }

    return physicsEntity;
}


void PhysicsSystem::applyMovementCommands(std::vector<std::shared_ptr<Entity>>&physicsEntity){
    for(auto& entity: physicsEntity){
        if(!entity->hasComponent<MovementCommandComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();        
        auto moveCommandComp = entity->getComponent<MovementCommandComponent>();

        if(moveCommandComp){
            if(moveCommandComp->moveCommandType == MovementCommandType::Hold){
                b2Body_SetLinearVelocity(physComp->body, {0, 0});
                // 무게를 늘린다던지.. 고정시켜서 움직이지 못하게
            }
            else if(moveCommandComp->moveCommandType == MovementCommandType::Stop){
                b2Body_SetLinearVelocity(physComp->body, {0, 0});
                // 행동은 멈추지만.. 다른 엔티티에 의해 밀릴 수 있음
            }
            else if(moveCommandComp->moveCommandType == MovementCommandType::Move){

            }
            else if(moveCommandComp->moveCommandType == MovementCommandType::GoForward){

                if(!entity->hasComponent<TransformComponent>() ||
                    (!entity->hasComponent<StatusComponent>() &&
                    !entity->hasComponent<ProjectileComponent>())) continue;

                auto transComp = entity->getComponent<TransformComponent>();
                float speed = 100.0f;
                float radian = toRadian(transComp->rotation);
                if(entity->hasComponent<ProjectileComponent>()){
                    auto projectileComp = entity->getComponent<ProjectileComponent>();
                    speed = projectileComp->projectileSpeed;
                }else if (entity->hasComponent<StatusComponent>()){
                    auto statusComp = entity->getComponent<StatusComponent>();
                    speed = statusComp->movementSpeed;
                }


                float forceMagnitude = speed / PIXELS_PER_METER; 

                b2Vec2 force = {forceMagnitude * cos(radian), forceMagnitude * sin(radian)};
                // 픽셀→미터 변환
                // std::cout << "go forward.   force :" << forceMagnitude * cos(radian) <<  ", " << forceMagnitude * sin(radian) << std::endl;

                b2Body_SetLinearVelocity(physComp->body, force);       
                // b2Body_ApplyForce(physComp->body, force, b2Body_GetWorldPoint(physComp->body, b2Body_GetPosition(physComp->body)), true);
            }
            else if(moveCommandComp->moveCommandType == MovementCommandType::Spin){
                if(!entity->hasComponent<TransformComponent>()) continue;

                auto transComp = entity->getComponent<TransformComponent>();
                transComp->rotation += 5.0f;

                b2Body_SetTransform(physComp->body, b2Body_GetPosition(physComp->body), b2MakeRot(toRadian(transComp->rotation)));
            }

        }
    }
}

void PhysicsSystem::setPositionsFromWorld(std::vector<std::shared_ptr<Entity>>&entities){

    for(auto& entity: entities){

        if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(physComp->hasBody()){
                        
            b2Vec2 pos = b2Body_GetPosition(physComp->body);
            b2Rot rot =  b2Body_GetRotation(physComp->body);
            float renderX = box2dToPixelX(pos.x) + (physComp->offsetX ? physComp->offsetX : 0.0f);
            float renderY = box2dToPixelY(pos.y) + (physComp->offsetY ? physComp->offsetY : 0.0f);
            
            auto posComp = entity->getComponent<PositionComponent>();
            if(posComp){
                posComp->set(renderX, renderY);
            }

            if(entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                if(transComp){
                    float box2dAngle = b2Rot_GetAngle(rot); 
                    // box2dAngle : 0 rad = 오른쪽
                    transComp->rotation = toAngle(box2dAngle); 
                    // => 0° = 오른쪽
                    // if(entity->hasComponent<ProjectileComponent>())std::cout << "Rotation : " << degAngle  << std::endl;
                }
            }

            if(entity->hasComponent<VelocityComponent>()){
                auto veloComp = entity->getComponent<VelocityComponent>();
                b2Vec2 b2Velocity = b2Body_GetLinearVelocity(physComp->body);
                
                // 만약 여러분의 좌표 변환이 픽셀 단위로 변환할 필요가 있다면, 아래와 같이 처리합니다.
                float pixelVx = b2Velocity.x * PIXELS_PER_METER;
                float pixelVy = b2Velocity.y * PIXELS_PER_METER;
                // 주의: y축이 반전되어 있다면, 필요에 따라 -를 붙여줍니다.
                // 예: float pixelVy = -b2Velocity.y * PIXELS_PER_METER;
                    
                Vector2D vec = {pixelVx, pixelVy};

                veloComp->set(vec);  // VelocityComponent에 업데이트
            }

        }
    }
}


void PhysicsSystem::getContactEvents(){
    b2ContactEvents ce = b2World_GetContactEvents(worldId);
    // BeginTouch
    for (int i = 0; i < ce.beginCount; i++) {
        // auto evt = ce.beginEvents + i;

        // CollisionEvent collision;
        // collision.type = CollisionType::Hit;
        // collision.entityA = shapeUserDataToEntity(evt->shapeIdA);
        // collision.entityB = shapeUserDataToEntity(evt->shapeIdB);
        // ecsManager->collisionEvents.push_back(collision);       
        // // shapeIdA, shapeIdB -> userData
        // push "CollisionBegin" event to ECS
    }

    b2SensorEvents se = b2World_GetSensorEvents(worldId);
    for (int i = 0; i < se.beginCount; i++) {
        auto evt = se.beginEvents + i;

        CollisionEvent collision;
        collision.type = CollisionType::Hit;
        collision.entityA = shapeUserDataToEntity(evt->sensorShapeId);
        collision.entityB = shapeUserDataToEntity(evt->visitorShapeId);
        ecsManager->collisionEvents.push_back(collision);       
        // shapeIdA, shapeIdB -> userData
        // push "CollisionBegin" event to ECS
    }

}


void PhysicsSystem::taskDestroyEvents(){
    auto evts = eventManager->getDestroyEvents();
    // BeginTouch
    for(auto evt : evts){
        auto entity = ecsManager->getEntityById(evt.entityId);
        destroyBody(entity);
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
    if (!entity) {
        std::cerr << "Entity not found for ID: " << entityId << std::endl;
        return nullptr;
    }
    return entity;
}

void PhysicsSystem::processDestroyQueue() {
    while (!destroyQueue.empty()) {
        if (b2Body_IsValid(destroyQueue.front())) {
            b2DestroyBody(destroyQueue.front());
            destroyQueue.pop();
        }        
    }
}