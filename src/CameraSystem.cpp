#include "Systems/CameraSystem.h"
#include "Groups.h"
#include "Components/CameraComponent.h"
#include "Components/PositionComponent.h"

#include <iostream>

void CameraSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity: entities){
		if(entity->hasComponent<PlayerTag>()) playerEntity = entity;			
		
	}
	cameraEntity = ecsManager->getCamera();

	if(playerEntity && cameraEntity){
		auto playerPosComp = playerEntity->getComponent<PositionComponent>();
		auto cameraComp = cameraEntity->getComponent<CameraComponent>();

		float targetX = (playerPosComp->x - (cameraComp->w / 2));
		float targetY = (playerPosComp->y - (cameraComp->h / 2));

	    cameraComp->x += (targetX - cameraComp->x) * 0.1f;
	    cameraComp->y += (targetY - cameraComp->y) * 0.1f;
		
		// int mapHeight = 900;
		// int mapWidth = 1600;
	    
	    // if (cameraComp->x < 0) cameraComp->x = 0;
	    // if (cameraComp->y < 0) cameraComp->y = 0;
	    // if (cameraComp->x > mapWidth - cameraComp->w) 
	    //     cameraComp->x = mapWidth - cameraComp->w;
	    // if (cameraComp->y > mapHeight - cameraComp->h)
	    //     cameraComp->y = mapHeight - cameraComp->h;
	}

}