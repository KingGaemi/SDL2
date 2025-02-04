#include "Systems/CameraSystem.h"
#include "Groups.h"
#include "Components/CameraComponent.h"
#include "Components/PositionComponent.h"
// #include "Components/TransformComponent.h"

#include <iostream>

void CameraSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){

	for(auto& entity: entities){
		if(entity->hasComponent<PlayerTag>()) playerEntity = entity;			
		
	}
	cameraEntity = ecsManager->getCamera();


	if(playerEntity && cameraEntity){
		auto playerPosComp = playerEntity->getComponent<PositionComponent>();
		auto cameraComp = cameraEntity->getComponent<CameraComponent>();
		auto cameraPosComp = cameraEntity->getComponent<PositionComponent>();

		if (!playerPosComp) {
	        std::cerr << "Player entity is missing PositionComponent!" << std::endl;
	        return;
	    }
	    if (!cameraComp) {
	        std::cerr << "Camera entity is missing CameraComponent!" << std::endl;
	        return;
	    }
	    if (!cameraPosComp) {
	        std::cerr << "Camera entity is missing PositionComponent!" << std::endl;
	        return;
	    }
		if(playerPosComp && cameraComp && cameraPosComp){
			float targetX = (playerPosComp->x - (cameraComp->w / 2));
			float targetY = (playerPosComp->y - (cameraComp->h / 2));
	
		    cameraPosComp->x += (targetX - cameraPosComp->x) * 0.1f;
		    cameraPosComp->y += (targetY - cameraPosComp->y) * 0.1f;

		    
		}
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