#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"






class EquipmentSlotsComponent : public Component{

public:
	EntityId weaponSlot;
	EntityId armorSlot;
};