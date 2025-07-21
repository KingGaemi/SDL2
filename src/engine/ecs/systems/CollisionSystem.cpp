#include "Systems/CollisionSystem.h"
#include "Components/ColliderComponent.h"
#include "Components/PositionComponent.h"
#include "Components/SolidComponent.h"
#include "Components/TransformComponent.h"
#include "Collision.h"

#include <iostream>

void CollisionSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
    auto colliders = getColliders(entities);

    if(!colliders.empty()){
        updateCollidersPosition(colliders);
        updateCollidersRotation(colliders);
        // checkCollisions(colliders);
    }
}

std::vector<std::shared_ptr<Entity>> CollisionSystem::getColliders(std::vector<std::shared_ptr<Entity>>& entities){
    std::vector<std::shared_ptr<Entity>> colliders;
    for (auto& entity : entities) {
        if (!entity->isActive) continue;
        if (entity->hasComponent<ColliderComponent>() &&
            entity->hasComponent<PositionComponent>()) {    
            colliders.push_back(entity);
        }
    }
    return colliders;
}

std::vector<std::shared_ptr<Entity>> CollisionSystem::getSolidColliders(std::vector<std::shared_ptr<Entity>>& entities){
    std::vector<std::shared_ptr<Entity>> colliders;
    for (auto& entity : entities) {
        if (!entity->isActive) continue;
        if (entity->hasComponent<ColliderComponent>() &&
            entity->hasComponent<PositionComponent>() &&
            entity->hasComponent<SolidComponent>()) {    
            colliders.push_back(entity);
        }
    }
    return colliders;
}

void CollisionSystem::updateCollidersPosition(std::vector<std::shared_ptr<Entity>>& colliders){

    for(auto& entity : colliders) {
        auto posComp = entity->getComponent<PositionComponent>();
        auto colComp = entity->getComponent<ColliderComponent>();

        // 매 프레임 '대입'
        colComp->collider.x = posComp->x + colComp->offsetX - colComp->collider.w/2.0f;
        colComp->collider.y = posComp->y + colComp->offsetY - colComp->collider.h/2.0f;
        // colComp->collider.x = posComp->x() + colComp->offsetX; etc...
    }
}

void CollisionSystem::updateCollidersRotation(std::vector<std::shared_ptr<Entity>>& colliders){

    for(auto& entity : colliders) {
        if(!entity->hasComponent<TransformComponent>()) continue;
        auto colComp = entity->getComponent<ColliderComponent>();
        auto transComp = entity->getComponent<TransformComponent>();
        // 매 프레임 '대입'
        colComp->rotation = transComp->rotation;
    }
}

void CollisionSystem::checkCollisions(std::vector<std::shared_ptr<Entity>>& colliders){

    for (int i = 0; i < (int)colliders.size(); i++){
        auto colA = colliders[i]->getComponent<ColliderComponent>();

        for (int j = i+1; j < (int)colliders.size(); j++){
            auto colB = colliders[j]->getComponent<ColliderComponent>();
            
            if (Collision::AABB(*colA, *colB)) {
                // 충돌 처리 (로그 출력, 이벤트, 데미지 등)

                CollisionEvent colEvt;
                colEvt.type = CollisionType::Hit;
                colEvt.entityA = colliders[i];
                colEvt.entityB = colliders[j];

                // std::cout << "Collision" <<std::endl;
                ecsManager->collisionEvents.push_back(colEvt);

            }
        }
    }
}
    
    