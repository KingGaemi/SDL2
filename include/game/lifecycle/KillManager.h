#pragma once
#include "engine/ecs/core/Entity.h"
#include <queue>


struct KillEvent
{
	std::shared_ptr<Entity> killer;
	std::shared_ptr<Entity> target;	
};



class KillManager {

public:

	std::queue<KillEvent> killEvents;


private:


};