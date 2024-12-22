#include "Systems/AttackSystem.h"
#include <iostream>







void AttackSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity : entities){

			auto stateComp = entity->getComponent<StateComponent>();

			if(stateComp && stateComp->callAttack){
					
				auto transComp = entity->getComponent<TransformComponent>();
				auto spriteComp = entity->getComponent<SpriteComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();


				if(transComp && spriteComp && statusComp){
					AttackRequest req;

					req.type = "slash";
					req.x = transComp->position.x + (spriteComp->dstRect.w / 3) + transComp->direction.x * 80;
					req.y = transComp->position.y + (spriteComp->dstRect.h / 3) + transComp->direction.y * 80;
					req.directionX = transComp->direction.x;
					req.directionY = transComp->direction.y;
					req.damage = statusComp->physicalDamage;
					req.scale = 1;
					req.duration = 0.1f;



					requests.push_back(req);

		
					stateComp->callAttack = false;

				}
			}

	}

}
