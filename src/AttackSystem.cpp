#include "Systems/AttackSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Groups.h"
#include <iostream>
#include <unordered_map>
#include <utility> // for std::pair




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
	}else if(event.attackType == AttackType::Shoot){
		shootArrow(event);
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

void AttackSystem::shootArrow(const AttackEvent& event){

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
		req.name = "arrow";
		req.x = posComp->x + directComp->hDir() * spriteComp->dstRect.w;
		req.y = posComp->y + directComp->vDir() * spriteComp->dstRect.h;


		req.hasTransform = true;
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		req.rotation = getAngleFromDirection(req.hDir, req.vDir);
		req.damage = statusComp->physicalDamage;
		req.hasDamage = true;
		req.sc = 1.0f;
		// req.projectileSpeed = 1.0f;
		req.teamCode = teamComp->teamCode;
		req.ownerId = entity->getID();
		req.hasOwner = true;
		req.hasVelocity = true;

		ecsManager->pendingSpawns.push_back(req);
	}
}



float AttackSystem::getAngleFromDirection(int hDir, int vDir) {
    static const std::map<std::pair<int, int>, float> directionToAngle = {
        {{ 0, -1}, 270.0f},  // 위쪽 (vDir = -1)
        {{ 1, -1}, 315.0f},  // 오른쪽 위
        {{ 1,  0}, 0.0f},    // 오른쪽
        {{ 1,  1}, 45.0f},   // 오른쪽 아래
        {{ 0,  1}, 90.0f},   // 아래쪽 (vDir = 1)
        {{-1,  1}, 135.0f},  // 왼쪽 아래
        {{-1,  0}, 180.0f},  // 왼쪽
        {{-1, -1}, 225.0f},  // 왼쪽 위
        {{ 0,  0}, 0.0f}     // 정지 (기본값)    // 정지 (기본값)
    };

    auto it = directionToAngle.find({hDir, vDir});
    if (it != directionToAngle.end()) {
        return it->second;
    }
    return 0.0f; // 기본값
}