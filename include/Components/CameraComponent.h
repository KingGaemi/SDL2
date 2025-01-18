#pragma once
#include "ECS/Component.h"


class CameraComponent : public Component {

public:
	int x, y;
	int w, h;
	CameraComponent(int w, int h) : w(w), h(h) {}

private:


};