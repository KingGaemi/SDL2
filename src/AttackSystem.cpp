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

						std::cout << spriteComp->dstRect.w << std::endl;
						req.x = posComp->x() + 20 + directComp->hDir() * spriteComp->dstRect.w;
						req.y = posComp->y() + directComp->vDir() * spriteComp->dstRect.h;
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
