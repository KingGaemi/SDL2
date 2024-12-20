#pragma once
#include "ECS/Component.h"



class LifeTimeComponent : public Component{

public:

	LifeTimeComponent() {}
	LifeTimeComponent(float lifeTime) : lifeTime(lifeTime) {}

	float lifeTime;

};