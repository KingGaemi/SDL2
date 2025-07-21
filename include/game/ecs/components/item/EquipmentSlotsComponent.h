#pragma once
#include "engine/ecs/core/Component.h"

#include "ecs/Entity.h"






class EquipmentSlotsComponent : public Component{

public:
	EntityId weaponSlot;
	EntityId armorSlot;
};