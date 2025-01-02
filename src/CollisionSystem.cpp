#include "Systems/CollisionSystem.h"
#include "Components/PositionComponent.h"

#include <iostream>

void CollisionSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

    std::vector<std::shared_ptr<Entity>> colliders;
    for (auto& entity : entities) {
        if (!entity->isActive) continue;
        if (entity->hasComponent<ColliderComponent>() &&
            entity->hasComponent<PositionComponent>()) {
            colliders.push_back(entity);
        }
    }

    for (auto& entity : colliders) {
        auto posComp = entity->getComponent<PositionComponent>();
        auto colComp = entity->getComponent<ColliderComponent>();

        // 매 프레임 '대입'
        colComp->collider.x = posComp->x() + colComp->offsetX - colComp->collider.w/2.0f;
        colComp->collider.y = posComp->y() + colComp->offsetY - colComp->collider.h/2.0f;
        // colComp->collider.x = posComp->x() + colComp->offsetX; etc...
    }


    for (int i = 0; i < (int)colliders.size(); i++){
        auto colA = colliders[i]->getComponent<ColliderComponent>();

        for (int j = i+1; j < (int)colliders.size(); j++){
            auto colB = colliders[j]->getComponent<ColliderComponent>();

            if (AABB(*colA, *colB)) {
                // 충돌 처리 (로그 출력, 이벤트, 데미지 등)

            	CollisionEvent colEvt;
            	colEvt.type = CollisionType::Hit;
            	colEvt.entityA = colliders[i];
            	colEvt.entityB = colliders[j];

                ecsManager->collisionEvents.push_back(colEvt);

            }
        }
    }
}



bool CollisionSystem::AABB(const Rect& recA , const Rect& recB){
		


		if(	
			recA.x + recA.w >= recB.x &&
			recB.x + recB.w >= recA.x &&
			recA.y + recA.h >= recB.y &&
			recB.y + recB.h >= recA.h)
		{
			return true;
		}

		return false;

}



bool CollisionSystem::AABB(const ColliderComponent& cA, const ColliderComponent& cB){
    // 표준 AABB 충돌 체크
    const Rect& a = cA.collider;
    const Rect& b = cB.collider;
    if (a.x < b.x + b.w  &&
        a.x + a.w > b.x  &&
        a.y < b.y + b.h  &&
        a.y + a.h > b.y)
    {
        return true;
    }
    return false;
}
