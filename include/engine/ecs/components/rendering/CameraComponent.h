#pragma once
#include "engine/ecs/core/Component.h"



class CameraComponent : public Component {

public:
	float x = 0;
	float y = 0;
	int w, h;
	CameraComponent(int w, int h) : w(w), h(h) {}

private:


};