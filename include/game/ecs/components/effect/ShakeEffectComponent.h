#pragma once
#include "engine/ecs/core/Component.h"



class ShakeEffectComponent : public Component {
public:
	float shakeTime = 0.0f;
	float shakeAmount = 1.0f;


};