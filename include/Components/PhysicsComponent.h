#pragma once
#include <box2d/box2d.h>
#include "ECS/Component.h"
#include "MyContactListener.h"


enum class BodyType{
	Kinematic,
	Static,
	Dynamic
};



class PhysicsComponent : public Component{

public:
	float x, y, w, h;
	float offsetX, offsetY, scale;
	float rotation = 0.0f; // angle

	BodyType bodyType;
	b2BodyId body = b2_nullBodyId;
	bool fixedRotation = false;


	PhysicsComponent(int pw, int ph, float sc, BodyType bodyType) : bodyType(bodyType) {
		x = 0;
		y = 0;
		w = pw * sc;
		h = ph * sc;
		offsetX = 0.0f;
		offsetY = 0.0f;
		rotation = 0.0f;
	}
	PhysicsComponent(int pw, int ph, float sc, float offX, float offY, float pRotation, BodyType bodyType, bool fixedRotation) : bodyType(bodyType), fixedRotation(fixedRotation) {
		x = 0;
		y = 0;
		w = pw * sc;
		h = ph * sc;
		offsetX = offX;
		offsetY = offY;
		rotation = pRotation;
	}

	bool hasBody() { return B2_IS_NON_NULL(body);}
};