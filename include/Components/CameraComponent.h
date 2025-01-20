#pragma once
#include "ECS/Component.h"


class CameraComponent : public Component {

public:
	int x = 0;
	int y = 0;
	int w, h;
	CameraComponent(int w, int h) : w(w), h(h) {}

private:


};