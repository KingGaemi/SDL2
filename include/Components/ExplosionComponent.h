#pragma once
#include "ECS/Component.h"


class ExplosionComponent : public Component{

public:

	ExplosionComponent() {}
	ExplosionComponent(float explosionAmount, float explosionTime) : explosionAmount(explosionAmount), explosionTime(explosionTime){
		currentTime = explosionTime;
	}

	float explosionAmount, explosionTime;
	float currentTime;
	bool readyToExplode = false;
	bool exploded = false;
};