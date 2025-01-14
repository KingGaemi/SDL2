#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
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