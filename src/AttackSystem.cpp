#include "Systems/AttackSystem.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/DirectionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "Components/SoundEffectComponent.h"
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
		if(event.abilityId == 1){
			castSpell(event);
		}else if(event.abilityId == 3){
			releaseBomb(event);
		}
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


	if(entity->hasComponent<SoundEffectComponent>()){
		auto soundComp = entity->getComponent<SoundEffectComponent>();
		auto type = soundComp->typeMaterial;

		soundManager->playEffect(type + "_swing");
	}

	if(posComp && directComp && spriteComp && statusComp && teamComp){
		
		SpawnRequest req;

		req.entityType = EntityType::Projectile;
		req.name = "slash";
		req.x = posComp->x + directComp->hDir() * spriteComp->dstRect.w/3;
		req.y = posComp->y + directComp->vDir() * spriteComp->dstRect.h/3;
		req.hasTransform = true;
		req.rotation = directComp->getAngle();
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		req.hasDirection = true;
		req.damage = statusComp->physicalDamage;
		req.hasDamage = true;
		req.sc = 1.0f;
		req.teamCode = teamComp->teamCode;
		req.ownerId = entity->getId();
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
		req.ownerId = entity->getId();
		req.hasOwner = true;

		// SpawnRequest req;

		// req.type = "box";

		// req.x = posComp->x() + directComp->hDir() * spriteComp->dstRect.w;
		// req.y = posComp->y() + directComp->vDir() * spriteComp->dstRect.h;

		ecsManager->pendingSpawns.push_back(req);
		req.x -= 3.0f;
		req.y -= 3.0f;
		ecsManager->pendingSpawns.push_back(req);
		req.x += 6.0f;
		req.y += 6.0f;
		ecsManager->pendingSpawns.push_back(req);
		ecsManager->pendingSpawns.push_back(req);

	}
}

void AttackSystem::shootArrow(const AttackEvent& event){

	auto entity = ecsManager->getEntityById(event.attackerId);
	if(!entity->isActive) return;

	auto posComp = entity->getComponent<PositionComponent>();
	auto directComp = entity->getComponent<DirectionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto statusComp = entity->getComponent<StatusComponent>();
	auto teamComp = entity->getComponent<TeamTag>();

	if(posComp && directComp && transComp && statusComp && teamComp){
		
		SpawnRequest req;

		req.entityType = EntityType::Projectile;
		req.name = "arrow";
		req.x = posComp->x + directComp->hDir() * transComp->width;
		req.y = posComp->y + directComp->vDir() * transComp->height;

		req.w = 0.0f; // origin
		req.h = 0.0f;
		req.hasTransform = true;
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		// std::cout << "direct" << req.hDir << ", "<< req.vDir <<std::endl;
		req.rotation = directComp->getAngle();
		// std::cout << "rotation" << req.rotation  <<std::endl;
		req.damage = statusComp->physicalDamage;
		req.hasDamage = true;
		req.sc = 2.0f;
		req.projectileSpeed = statusComp->projectileSpeedMultiple;
		if(req.hDir != 0 && req.vDir != 0) req.projectileSpeed /= 1.414f;
		req.teamCode = teamComp->teamCode;

		// std::cout << teamComp->getTeamString() <<std::endl;
		req.ownerId = entity->getId();
		req.hasOwner = true;
		req.hasVelocity = false;

		ecsManager->pendingSpawns.push_back(req);
	}
}

void AttackSystem::whirlBlade(const AttackEvent& event){

	auto entity = ecsManager->getEntityById(event.attackerId);
	if(!entity->isActive) return;

	auto posComp = entity->getComponent<PositionComponent>();
	auto directComp = entity->getComponent<DirectionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto statusComp = entity->getComponent<StatusComponent>();
	auto teamComp = entity->getComponent<TeamTag>();

	if(posComp && directComp && transComp && statusComp && teamComp){
		
		SpawnRequest req;

		req.entityType = EntityType::Projectile;
		req.name = "streetlamp";
		req.x = posComp->x + directComp->hDir() * transComp->width;
		req.y = posComp->y + directComp->vDir() * transComp->height;
		req.w = 0;
		req.h = 0;
		req.hasTransform = true;
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		req.hasDirection = true;
		req.rotation = directComp->getAngle();

		req.damage = statusComp->physicalDamage;
		req.hasDamage = true;
		req.sc = 0.5f;
		req.projectileSpeed = statusComp->projectileSpeedMultiple;
		if(req.hDir != 0 && req.vDir != 0) req.projectileSpeed /= 1.414f;
		req.teamCode = teamComp->teamCode;
		req.ownerId = entity->getId();
		req.hasOwner = true;
		req.hasVelocity = true;

		ecsManager->pendingSpawns.push_back(req);
	}
}


void AttackSystem::releaseBomb(const AttackEvent& event){

	auto entity = ecsManager->getEntityById(event.attackerId);
	if(!entity->isActive) return;

	auto posComp = entity->getComponent<PositionComponent>();
	auto directComp = entity->getComponent<DirectionComponent>();
	auto transComp = entity->getComponent<TransformComponent>();
	auto statusComp = entity->getComponent<StatusComponent>();
	auto teamComp = entity->getComponent<TeamTag>();

	if(posComp && directComp && transComp && statusComp && teamComp){
		
		SpawnRequest req;

		req.entityType = EntityType::Object;
		req.name = "barrel";
		req.x = posComp->x + directComp->hDir() * transComp->width;
		req.y = posComp->y + directComp->vDir() * transComp->height;
		req.w = 0;
		req.h = 0;
		// req.hasTransform = true;
		req.hDir = directComp->direction.hDir;
		req.vDir = directComp->direction.vDir;
		// req.hasDirection = true;
		// req.rotation = directComp->getAngle();

		req.damage = statusComp->physicalDamage;
		req.hasDamage = true;
		req.sc = 1.0f;
		req.teamCode = teamComp->teamCode;
		req.ownerId = entity->getId();
		req.hasOwner = true;

		ecsManager->pendingSpawns.push_back(req);
	}
}




