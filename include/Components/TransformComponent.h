#pragma once

#include "ECS/Component.h"
#include "Vector2D.h"
#include <math.h>

class TransformComponent : public Component {
public:


    int width = 32;    // 그래픽/충돌 용도
    int height = 32;
    float scale = 1;

    float rotation = 0.0f;

    // bool isMoving = false; // 이동 중인지 여부(선택적으로 유지)

    TransformComponent() {}
    TransformComponent(int w, int h, float sc)
        : width(w), height(h), scale(sc) {}

    float getRadian(){
    	return rotation*(3.14159f / 180.0f);
    }

    // 필요하다면 생성자/메서드 더 추가

	// Vector2D position;
	// Vector2D velocity;
	// Direction direction;

	// int width = 32;
	// int height = 32;
	// int scale = 1;

	// bool isMoving = false;

	// TransformComponent(){}
	// TransformComponent(int sc){scale = sc;}
	// TransformComponent(Vector2D vector){position = vector;}
	// TransformComponent(float x, float y){position.x = x; position.y = y;}
	// TransformComponent(float x, float y, Direction dir){position.x = x; position.y = y; direction = dir;}
	// TransformComponent(float x, float y, int sc){position.x = x; position.y = y; scale = sc; }
	// TransformComponent(float x, float y,  Direction dir, int sc){position.x = x; position.y = y;  direction = dir; scale = sc;}
	// TransformComponent(float x, float y, int w, int h, int sc){position.x = x; position.y = y; width = w; height = h; scale = sc;}

	// float x(){return position.x;}
	// float y(){return position.y;}
	// void x(float x) {position.x = x;}
	// void y(float y) {position.y = y;}


	// void setPos(float x, float y){ position.x = x; position.y = y;}
	// void setPos(Vector2D vector){ position = vector;}

	// void setVel(float x, float y) { velocity.x = x; velocity.y = y;}
	// void setVelx(float x) {velocity.x = x;}
	// void setVely(float y) {velocity.y = y;}
	// void setDirectionX(int x) {direction.x = x;}
	// void setDirectionY(int y) {direction.y = y;}
 	// void addVel(float x, float y) { velocity.x += x; velocity.y += y;}
 	// void addVel(const Vector2D& velo) { velocity.x += velo.x; velocity.y += velo.y;}
	// int getVelx() {return velocity.x;}
	// int getVely() {return velocity.y;}

	// void setMoving(bool moving) {isMoving = moving ;}

private:




};