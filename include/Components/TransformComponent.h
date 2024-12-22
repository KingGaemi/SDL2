#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"


struct Direction{
	int x = 0;
	int y = 0;
};


class TransformComponent : public Component {
public:

	Vector2D position;
	Vector2D velocity;
	Direction direction;

	int width = 32;
	int height = 32;
	int scale = 1;

	bool isMoving = false;

	TransformComponent(){}
	TransformComponent(int sc){scale = sc;}
	TransformComponent(Vector2D vector){position = vector;}
	TransformComponent(float x, float y){position.x = x; position.y = y;}
	TransformComponent(float x, float y, Direction dir){position.x = x; position.y = y; direction = dir;}
	TransformComponent(float x, float y, int sc){position.x = x; position.y = y; scale = sc; }
	TransformComponent(float x, float y,  Direction dir, int sc){position.x = x; position.y = y;  direction = dir; scale = sc;}
	TransformComponent(float x, float y, int w, int h, int sc){position.x = x; position.y = y; width = w; height = h; scale = sc;}

	float x(){return position.x;}
	float y(){return position.y;}
	void x(float x) {position.x = x;}
	void y(float y) {position.y = y;}


	void setPos(float x, float y){ position.x = x; position.y = y;}
	void setPos(Vector2D vector){ position = vector;}

	void setVel(float x, float y) { velocity.x = x; velocity.y = y;}
	void setVelx(float x) {velocity.x = x;}
	void setVely(float y) {velocity.y = y;}
	void setDirectionX(int x) {direction.x = x;}
	void setDirectionY(int y) {direction.y = y;}
 	void addVel(float x, float y) { velocity.x += x; velocity.y += y;}
	int getVelx() {return velocity.x;}
	int getVely() {return velocity.y;}

	void setMoving(bool moving) {isMoving = moving ;}

private:




};