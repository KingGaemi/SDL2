#include "Systems/AttackSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Groups.h"
#include <iostream>




void AttackSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity : entities){
		if(!entity->isActive) continue;

		if(entity->hasComponent<StateComponent>() ){
			auto stateComp = entity->getComponent<StateComponent>();

			if(stateComp && stateComp->callAttack){
					
				auto posComp = entity->getComponent<PositionComponent>();
				auto directComp = entity->getComponent<DirectionComponent>();
				auto spriteComp = entity->getComponent<SpriteComponent>();
				auto statusComp = entity->getComponent<StatusComponent>();
				auto teamComp = entity->getComponent<TeamTag>();
				
				if(posComp && directComp && spriteComp && statusComp && teamComp){
					
					SpawnRequest req;

					req.entityType = EntityType::Projectile;
					req.name = "slash";
			
					req.x = posComp->x + directComp->hDir() * spriteComp->dstRect.w;
					req.y = posComp->y + directComp->vDir() * spriteComp->dstRect.h;
					req.hasTransform = false;
					req.hDir = directComp->direction.hDir;
					req.vDir = directComp->direction.vDir;
					req.damage = statusComp->physicalDamage;
					req.hasDamage = true;
					req.sc = 1.0f;
					req.teamCode = teamComp->teamCode;
					req.ownerId = entity->getID();
					req.hasOwner = true;

					// SpawnRequest req;

					// req.type = "box";

					// req.x = posComp->x() + directComp->hDir() * spriteComp->dstRect.w;
					// req.y = posComp->y() + directComp->vDir() * spriteComp->dstRect.h;

					ecsManager->pendingSpawns.push_back(req);

					stateComp->callAttack = false;

				}
			}
		}
	}
}
