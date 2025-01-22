#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/SolidComponent.h"



void MovementSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) {

    for (auto& entity : entities) {

        if(entity->isActive && entity->hasComponent<VelocityComponent>() && !entity->hasComponent<PhysicsComponent>()){

            auto posComp = entity->getComponent<PositionComponent>();
            auto veloComp = entity->getComponent<VelocityComponent>();
            if (!posComp || !veloComp) continue;
            
            // Vector2D preMove = posComp->position + veloComp->velo() * deltaTime;
            if(veloComp->x() != 0 && veloComp->y() != 0){
                posComp->set(posComp->x + veloComp->x() * deltaTime *0.8f, posComp->y + veloComp->y() * deltaTime *0.8f);
            }else{
                posComp->set(posComp->x + veloComp->x() * deltaTime, posComp->y + veloComp->y() * deltaTime);
            }


            // if(entity->hasComponent<SolidComponent>){

            //     auto colliders = CollisionSystem::getSolidColliders(entities);

            // } 






        }
    }

}

