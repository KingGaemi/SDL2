#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"



class TransformComponent : public Component {
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent(){}
	TransformComponent(int sc){scale = sc;}
	TransformComponent(float x, float y){position.x = x; position.y = y;}
	TransformComponent(float x, float y, int sc){position.x = x; position.y = y; scale = sc;}
	TransformComponent(float x, float y, int w, int h, int sc){position.x = x; position.y = y; width = w; height = h; scale = sc;}

	float x(){return position.x;}
	float y(){return position.y;}
	void x(float x) {position.x = x;}
	void y(float y) {position.y = y;}


	void setPos(float x, float y){ position.x = x; position.y = y;}
	void setVel(float x, float y) { velocity.x = x; velocity.y = y;}

private:




};