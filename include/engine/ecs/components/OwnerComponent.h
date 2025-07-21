#pragma once
#include "engine/ecs/core/Component.h"

#include <memory>



class OwnerComponent : public Component{
public:
	std::size_t ownerId;
};