#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/ecs/core/Entity.h"
#include <vector>


using ItemId = std::size_t;


class ItemComponent : public Component{

public:
	ItemId itemId;
	std::string displayName;
	std::string discription;

	bool consumed = false;
	bool onField = true;
	bool stackable;
	int maxStackCounts;
	int currentStack = 1;

	ItemComponent(ItemId itemId, bool stackable, int maxStackCounts ) : itemId(itemId), stackable(stackable), maxStackCounts(maxStackCounts) {  } 

};