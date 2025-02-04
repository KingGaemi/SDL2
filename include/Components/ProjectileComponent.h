#pragma once
#include "ECS/Component.h"



class ProjectileComponent : public Component{
public:

	float projectileSpeed;
	float projectileScale;
	float duration;
	int penetration = 0;

	ProjectileComponent(float projectileSpeed, float projectileScale, float duration, int penetration) :
	projectileSpeed(projectileSpeed) , projectileScale(projectileScale), duration(duration), penetration(penetration) {}

};