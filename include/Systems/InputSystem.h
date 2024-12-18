#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"




class InputSystem : public System{

public:


	void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;


};