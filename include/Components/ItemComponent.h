#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include <vector>


using ItemId = std::size_t;


class ItemComponent : public Component{

public:
	ItemId itemId;
	std::string displayName;
	std::string discription;

	bool stackable;
	int maxStackCounts;

	ItemComponent(ItemId itemId, bool stackable, int maxStackCounts ) : itemId(itemId), stackable(stackable), maxStackCounts(maxStackCounts) {} 

};