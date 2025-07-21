#pragma once
#include "engine/ecs/core/Component.h"

#include "Rect.h"
#include <string>
#include <cmath>


class ShadowComponent : public Component{
public:
	ShadowComponent(float w, float h, float psc, float offsetX, float offsetY) : offsetX(offsetX), offsetY(offsetY){
        w = std::round(w * 10) / 10;
    	h = std::round(h * 10) / 10;
		srcRect = {0, 0, static_cast<int>(w), static_cast<int>(h)};
		dstRect = {0, 0, w*psc, h*psc};
		sc = psc;
	}
	
	float offsetX, offsetY;
	float sc;
	Rect srcRect;
	FRect dstRect;

private:
};