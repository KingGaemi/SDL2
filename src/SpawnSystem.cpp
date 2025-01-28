#include "Systems/SpawnSystem.h"
#include "Components/SpawnerComponent.h"
#include "Components/PositionComponent.h"
#include "Components/TransformComponent.h"



void SpawnSystem::update(std::vector<std::shared_ptr<Entity>>&entities, float deltaTime){

	for(auto& entity: entities){
		if(entity->hasComponent<SpawnerComponent>()&&
			entity->hasComponent<PositionComponent>()&&
			entity->hasComponent<TransformComponent>()){

			auto posComp = entity->getComponent<PositionComponent>();
			auto spawnComp = entity->getComponent<SpawnerComponent>();
			auto transComp = entity->getComponent<TransformComponent>();
			auto spawnList = spawnComp->spawnList;


			for(auto req : spawnList){
				if(spawnComp->currentLeftTime <= 0){
					req.name = "slime1";
					req.x = getRandomNumber(static_cast<int>(posComp->x - (transComp->width)/2),
										   static_cast<int>(posComp->x + (transComp->width)/2));
					req.y = getRandomNumber(static_cast<int>(posComp->y - (transComp->height)/2),
										   static_cast<int>(posComp->y + (transComp->height)/2));
					
					ecsManager->pendingSpawns.push_back(req);
					spawnComp->currentLeftTime = spawnComp->spawnTime;
				}else{
					spawnComp->currentLeftTime -= deltaTime;
				}
			}
		}
	}
}