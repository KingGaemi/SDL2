#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include <vector>





class InventoryComponent : public Component{

public:
	std::vector<EntityID> items;
	std::string InventorytextureID;
	int maxSlots = 10;

	InventoryComponent(int maxSlots) : maxSlots(maxSlots) {} 

};