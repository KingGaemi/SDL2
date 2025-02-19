#include "Systems/PhysicsSystem.h"
#include "Components/PositionComponent.h"
#include "Components/PhysicsComponent.h"
// #include "Components/ColliderComponent.h"
#include "Components/MovementCommandComponent.h"
#include "Components/TransformComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/PlayableComponent.h"
#include "Components/ProjectileComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/HitboxComponent.h"
#include "Groups.h"

#include "myMath.h"
#include <iostream>


// #include <math>



void PhysicsSystem::init() {

 	worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    worldId = b2CreateWorld(&worldDef);

}


void PhysicsSystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){
    cleanUpDeadBodies(entities);
    createBodies(entities);
    setBeforeStep(entities);
    b2World_Step(worldId, deltaTime, subStepCount);
    getContactEvents();
    taskDestroyEvents();
    processDestroyQueue();
    setPositionsFromWorld(entities);
}


void PhysicsSystem::cleanUpDeadBodies(std::vector<std::shared_ptr<Entity>>& entities) {
    for(auto& entity :entities){
        if (entity->hasComponent<PhysicsComponent>() && entity->hasComponent<StatusComponent>()){
            auto physComp = entity->getComponent<PhysicsComponent>();
            auto statusComp = entity->getComponent<StatusComponent>();
            if(!statusComp->isAlive){                
                if (physComp->hasBody()) {
                    // 맵에서 제거
                    auto it = bodyMap.find(entity->getId());
                    if (it != bodyMap.end()) {
                        bodyMap.erase(it);
                    }
                    if (b2Body_IsValid(physComp->body)) {
                        b2DestroyBody(physComp->body);
                        // std::cout<< "destroyBody " << std::endl;
                    }        
                    physComp->body = b2_nullBodyId;
                }
            }            
        }
    }
}

void PhysicsSystem::createWalls(){

    

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
        auto statusComp = entity->getComponent<StatusComponent>();
        if(statusComp && !statusComp->isAlive) continue;
        
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
                      (posComp->y) / PIXELS_PER_METER};

            auto transComp = entity->getComponent<TransformComponent>();
            // (1) TransformComponent->rotation : 0°=오른쪽
            // (2) toRadian() : 도→라디안, 0도 -> 0라디안
            if (transComp) {
                bodyDef.rotation.c = cos(transComp->radian);
                bodyDef.rotation.s = sin(transComp->radian);
            }

            bodyDef.linearDamping = 10.0f;
            if(entity->hasComponent<ProjectileComponent>()) bodyDef.linearDamping = 0.0f;
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
                hitboxShapeDef.enableSensorEvents = true;
                hitboxShapeDef.isSensor = true;
                b2CreatePolygonShape(physComp->body, &hitboxShapeDef, &hitbox);
            }
        }
    }
}


void PhysicsSystem::setBeforeStep(std::vector<std::shared_ptr<Entity>>&entities){

    std::vector<std::shared_ptr<Entity>> physicsEntity;

    for(auto& entity: entities){
        if(entity->hasComponent<PhysicsComponent>()) physicsEntity.push_back(entity);
    }

    setInfoFromGame(physicsEntity);
    applyMovementCommands(physicsEntity);

    // etc..
}



void PhysicsSystem::setInfoFromGame(std::vector<std::shared_ptr<Entity>>&entities){

    for(auto& entity: entities){

        if(!entity->isActive || !entity->hasComponent<PhysicsComponent>() || !entity->hasComponent<PositionComponent>()) continue;

        auto physComp = entity->getComponent<PhysicsComponent>();

        if(physComp->hasBody()){
            
            if (entity->hasComponent<VelocityComponent>()) {
                // velocityComponent 등에서 얻은 vx, vy
                auto veloComp = entity->getComponent<VelocityComponent>();

                // 픽셀→미터 변환
                float vx = veloComp->x() / PIXELS_PER_METER; // pixel/sec or so
                float vy = veloComp->y() / PIXELS_PER_METER; // sdl2와 box2의 y 방향은 반대
                
                b2Vec2 vel;
                vel.x = vx;
                vel.y = vy;

                b2Body_SetLinearVelocity(physComp->body, vel);                
            }
            if (entity->hasComponent<TransformComponent>() && entity->hasComponent<PositionComponent>()) {
                // TransformComponent에서 위치와 회전값 가져오기
                // auto transComp = entity->getComponent<TransformComponent>();
                // auto posComp = entity->getComponent<PositionComponent>();             

                // b2Vec2 pos = (b2Vec2){(posComp->x) / PIXELS_PER_METER,
                //       (posComp->y) / PIXELS_PER_METER};
                // b2Rot rot = b2MakeRot(transComp->radian);


                // b2Body_SetTransform(physComp->body, pos, rot);                
            }

        }
    }

}


void PhysicsSystem::applyMovementCommands(std::vector<std::shared_ptr<Entity>>&physicsEntity){
    if (physicsEntity.empty()) return;
    for(auto& entity: physicsEntity){
        if(!entity->hasComponent<MovementCommandComponent>()) continue;
        if(!entity->hasComponent<PhysicsComponent>()) continue; 
        auto physComp = entity->getComponent<PhysicsComponent>();        
        auto moveCommandComp = entity->getComponent<MovementCommandComponent>();
        auto stateComp = entity->getComponent<StateComponent>();
        auto statusComp = entity->getComponent<StatusComponent>();
        auto directComp = entity->getComponent<DirectionComponent>();
        auto veloComp = entity->getComponent<VelocityComponent>();
        if(moveCommandComp && physComp){
            MovementCommand moveCommand;
            while(moveCommandComp->pop(moveCommand)){
                if (!b2Body_IsValid(physComp->body)) {
                    // std::cerr << "Error: Attempted to access to an invalid body!\n";
                    continue;
                }
                if(moveCommand.moveCommandType == MovementCommandType::Hold){
                    b2Body_SetLinearVelocity(physComp->body, {0, 0});
                    // 무게를 늘린다던지.. 고정시켜서 움직이지 못하게
                }
                else if(moveCommand.moveCommandType == MovementCommandType::Stop){
                    // 행동은 멈추지만.. 다른 엔티티에 의해 밀릴 수 있음
                    if(stateComp)stateComp->changeMovementState(MovementStates::Stop);
                    b2Body_SetLinearVelocity(physComp->body, {0, 0});                    
                }
                else if(moveCommand.moveCommandType == MovementCommandType::MoveToDirection){

                    if(!stateComp || !statusComp || !directComp || !veloComp) continue;
                    if(stateComp->movementState == MovementStates::Stop){
                        stateComp->changeMovementState(MovementStates::Walk);
                    }
                    if(moveCommand.doubleTap){
                        stateComp->changeMovementState(MovementStates::Run);
                    }

                    // break when go opposite
                    if(stateComp->movementState == MovementStates::Run){
                        if((moveCommand.direction.hDir == -1 && directComp->direction.hDir == 1) ||
                            (moveCommand.direction.hDir == 1 && directComp->direction.hDir == -1) ||
                            (moveCommand.direction.vDir == -1 && directComp->direction.vDir == 1) ||
                            (moveCommand.direction.vDir == 1 && directComp->direction.vDir == -1)){
                            stateComp->changeMovementState(MovementStates::Walk);
                        } 
                    }

                    directComp->direction = moveCommand.direction;
                    Vector2D velo = directComp->dirToVector();                          
                    velo = velo * (statusComp->movementSpeed / PIXELS_PER_METER);
                    if(stateComp->movementState == MovementStates::Run){                    
                        velo = velo * statusComp->runningSpeedMultiple;
                    }else{
                    
                    }

                    // Adjust diagonal movement speed
                    int dir = directComp->direction.hDir + directComp->direction.vDir;
                    if(dir == 0 || dir == 2 || dir == -2){
                        velo = velo * 0.8f;
                    }
                    b2Vec2 vec = {velo.x , velo.y};

                    b2Body_SetLinearVelocity(physComp->body, vec);

                }else if(moveCommand.moveCommandType == MovementCommandType::GoForward){

                    if(!entity->hasComponent<TransformComponent>() ||
                        (!entity->hasComponent<StatusComponent>() &&
                        !entity->hasComponent<ProjectileComponent>())) continue;

                    auto transComp = entity->getComponent<TransformComponent>();
                    float speed = 100.0f;
                    
                    if(entity->hasComponent<ProjectileComponent>()){
                        auto projectileComp = entity->getComponent<ProjectileComponent>();
                        speed = projectileComp->projectileSpeed;
                    }else if (entity->hasComponent<StatusComponent>()){
                        auto statusComp = entity->getComponent<StatusComponent>();
                        speed = statusComp->movementSpeed;
                    }


                    float forceMagnitude = speed / PIXELS_PER_METER; 

                    b2Vec2 force = {forceMagnitude * cos(transComp->radian), forceMagnitude * sin(transComp->radian)};
                    // 픽셀→미터 변환
                    // std::cout << "go forward.   force :" << forceMagnitude * cos(radian) <<  ", " << forceMagnitude * sin(radian) << std::endl;

                    // b2Body_ApplyForceToCenter(physComp->body, force, true);
                     if(moveCommand.stopSpin)  b2Body_SetAngularVelocity(physComp->body, 0);
                    b2Body_SetLinearVelocity(physComp->body, force);
                    // b2Body_ApplyForce(physComp->body, force, b2Body_GetWorldPoint(physComp->body, b2Body_GetPosition(physComp->body)), true);
                }else if(moveCommand.moveCommandType == MovementCommandType::Spin){
                    if(moveCommand.isClockwise){
                        b2Body_SetAngularVelocity(physComp->body, -5.0f);
                    }else{
                        b2Body_SetAngularVelocity(physComp->body, 5.0f);
                    }
                    if(moveCommand.stopSpin)  b2Body_SetAngularVelocity(physComp->body, 0);
                }else if(moveCommand.moveCommandType == MovementCommandType::Impulse){
                    b2Vec2 vec = {cos(moveCommand.radian), sin(moveCommand.radian)};
                    b2Body_ApplyLinearImpulseToCenter(physComp->body, vec, true);
                }
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
            float renderX = box2dToPixelX(pos.x);
            float renderY = box2dToPixelY(pos.y);
            
            auto posComp = entity->getComponent<PositionComponent>();
            if(posComp){
                posComp->set(renderX, renderY);
            }

            if(entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                if(transComp){                    
                    // box2dAngle : 0 rad = 오른쪽
                    transComp->radian = b2Rot_GetAngle(rot); 
                    // => 0° = 오른쪽
                    // if(entity->hasComponent<ProjectileComponent>())std::cout << "Rotation : " << transComp->radian  << std::endl;
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