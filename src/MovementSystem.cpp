#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SolidComponent.h"



void MovementSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) {

    for (auto& entity : entities) {

        if(entity->isActive && entity->hasComponent<VelocityComponent>()){

            auto posComp = entity->getComponent<PositionComponent>();
            auto veloComp = entity->getComponent<VelocityComponent>();
            if (!posComp || !veloComp) continue;

            Vector2D origin = posComp->position;
            // Vector2D preMove = posComp->position + veloComp->velo() * deltaTime;
            posComp->set(posComp->position + veloComp->velo() * deltaTime);


            // if(entity->hasComponent<SolidComponent>){

            //     auto colliders = CollisionSystem::getSolidColliders(entities);

            // } 






        }
    }

}

