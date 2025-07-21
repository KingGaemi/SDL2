#pragma once
#include "engine/ecs/core/Component.h"




class PlayableComponent : public Component{
	bool playable = true;
};