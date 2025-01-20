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

	AttackEvent event;
	while(eventManager->pollAttackEvent(event)){
		teskEvent(event);
	}
	
}

void AttackSystem::teskEvent(const AttackEvent& event){

	if(event.attackType == AttackType::Attack){
		basicAttack(event);
	}else if(event.attackType == AttackType::Cast){
		castSpell(event);
	}else{

	}
	
}


void AttackSystem::basicAttack(const AttackEvent& event){

	auto entity = ecsManager->getEntityById(event.attackerId);
	if(!entity->isActive) return;

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
	}
}

void AttackSystem::castSpell(const AttackEvent& event){

	auto entity = ecsManager->getEntityById(event.attackerId);
	if(!entity->isActive) return;

	auto posComp = entity->getComponent<PositionComponent>();
	auto directComp = entity->getComponent<DirectionComponent>();
	auto spriteComp = entity->getComponent<SpriteComponent>();
	auto statusComp = entity->getComponent<StatusComponent>();
	auto teamComp = entity->getComponent<TeamTag>();

	if(posComp && directComp && spriteComp && statusComp && teamComp){
		
		SpawnRequest req;

		req.entityType = EntityType::Projectile;
		req.name = "box";
		req.x = posComp->x + directComp->hDir() * spriteComp->dstRect.w;
		req.y = posComp->y + directComp->vDir() * spriteComp->dstRect.h;
		req.hasTransform = false;
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		req.damage = statusComp->physicalDamage;
		req.hasDamage = false;
		req.sc = 1.0f;
		req.teamCode = teamComp->teamCode;
		req.ownerId = entity->getID();
		req.hasOwner = true;

		// SpawnRequest req;

		// req.type = "box";

		// req.x = posComp->x() + directComp->hDir() * spriteComp->dstRect.w;
		// req.y = posComp->y() + directComp->vDir() * spriteComp->dstRect.h;

		ecsManager->pendingSpawns.push_back(req);
	}
}
