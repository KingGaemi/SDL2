#include "Systems/AttackSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"


#include <iostream>







void AttackSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity : entities){

			if(entity->hasComponent<StateComponent>()){
				auto stateComp = entity->getComponent<StateComponent>();

				if(stateComp && stateComp->callAttack){
						
					auto posComp = entity->getComponent<PositionComponent>();
					auto directComp = entity->getComponent<DirectionComponent>();
					auto spriteComp = entity->getComponent<SpriteComponent>();
					auto statusComp = entity->getComponent<StatusComponent>();


					if(posComp && directComp && spriteComp && statusComp){
						AttackRequest req;

						req.type = "slash";
						req.x = posComp->x() + (spriteComp->dstRect.w / 3) + directComp->hDir() * 80;
						req.y = posComp->y() + (spriteComp->dstRect.h / 3) + directComp->vDir() * 80;
						req.hDir = directComp->direction.hDir;
						req.vDir = directComp->direction.vDir;
						req.damage = statusComp->physicalDamage;
						req.scale = 1;
						req.duration = 0.1f;



						requests.push_back(req);

			
						stateComp->callAttack = false;

					}
				}
			}

	}

}
