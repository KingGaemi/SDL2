#pragma once

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "Components/MapComponent.h"




class MapInitializationSystem : public System{

public:

	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
		for(auto& entity : entities){
			entity->hasComponent<MapComponent>();
		}
	}
	MapInitializationSystem() {}

};