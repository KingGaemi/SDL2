#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

class HpBarComponent : public Component {

public:
	HpBarComponent(int w, int h, int type, float offsetY, float scale) : w(w), h(h), type(type), offsetY(offsetY), sc(scale) {}

	float percentage;
	int w, h, type;
	float offsetY, offsetX;
	float sc;



private:

};