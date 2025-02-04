#pragma once

#include "ECS/Component.h"



class HitboxComponent : public Component{

public:
	int w, h;
	float offsetX, offsetY;
	float sc;
	// float radian;

	HitboxComponent(int width, int height, float offsetX, float offsetY, float scale) : offsetX(offsetX), offsetY(offsetY), sc(scale) {
		w = width*scale;
		h = height*scale;

	}

};