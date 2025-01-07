#pragma once
#include "ECS/Component.h"
#include <memory>



class OwnerComponent : public Component{
public:
	std::size_t ownerId;
};