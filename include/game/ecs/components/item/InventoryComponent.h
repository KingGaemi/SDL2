#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/ecs/core/Entity.h"
#include <vector>





class InventoryComponent : public Component{

public:
	std::vector<EntityID> items;
	std::string InventorytextureID;
	int maxSlots = 10;

	int gold = 0;
	int maxGold = 99999999;



	InventoryComponent(int maxSlots) : maxSlots(maxSlots) {}

	

	void increaseGold(int amount) {
		gold += amount;
		if(gold > maxGold) gold = maxGold;
	}

};