#pragma once

#include "engine/ecs/core/System.h"
#include "engine/ecs/core/Entity.h"




class InputSystem : public System{

public:


	void update(float deltaTime) override;


};