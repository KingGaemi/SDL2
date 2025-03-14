#pragma once
#include "ECS/Component.h"



class ProjectileComponent : public Component{
public:

	float projectileSpeed;
	float projectileScale;
	float duration;
	int penetration = 0;
	std::size_t ownerId;
	std::string attackType = "none";

	ProjectileComponent(float projectileSpeed, float projectileScale, float duration, int penetration, std::string attackType) :
	projectileSpeed(projectileSpeed) , projectileScale(projectileScale), duration(duration), penetration(penetration), attackType(attackType) {}

}; 