#pragma once
#include "engine/ecs/core/Component.h"

#include "engine/ecs/core/Entity.h"






class EquipmentSlotsComponent : public Component{

public:
	EntityId weaponSlot;
	EntityId armorSlot;
};