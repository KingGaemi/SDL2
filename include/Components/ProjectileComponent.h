#pragma once
#include "ECS/Component.h"



class ProjectileComponent : public Component{
public:

	float projectileSpeed;
	float projectileScale;
	float duration;

	ProjectileComponent(float projectileSpeed, float projectileScale, float duration) :
	projectileSpeed(projectileSpeed) , projectileScale(projectileScale), duration(duration) {}

};