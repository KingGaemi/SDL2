#pragma once
#include <box2d/box2d.h>
#include "ECS/Component.h"



enum class BodyType{
	Kinematic,
	Static,
	Dynamic

};



class PhysicsComponent : public Component{

public:
	BodyType bodyType;
	b2BodyId body = b2_nullBodyId;

	PhysicsComponent(BodyType bodyType) : bodyType(bodyType) {}

	bool hasBody() { return B2_IS_NON_NULL(body);}



};