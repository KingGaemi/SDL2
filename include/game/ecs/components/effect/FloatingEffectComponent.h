#pragma once
#include "engine/ecs/core/Component.h"

class FloatingEffectComponent : public Component{
public:
	float amplitude = 4.0f;
    float speed = 3.0f;
    float renderOffsetY = 0.0f;  // 아이템마다 다른 타이밍을 주고 싶으면
    float originalY = 0;    // 최초 y값
    float timeElapsed = 0;
    float phaseOffset = 0;

};