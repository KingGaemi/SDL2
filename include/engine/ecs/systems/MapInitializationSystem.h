#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"
#include "game/map/MapComponent.h"




class MapInitializationSystem : public System{

public:

	void update(float deltaTime){
		for(auto& entity : entities){
			entity->hasComponent<MapComponent>();
		}
	}
	MapInitializationSystem() {}

};