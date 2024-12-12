#pragma once
#include <string>
#include "ECS/Component.h"


class SpriteComponent : public Component{

public:

	int width;
	int height;
	float scale = 1.0f;


	SpriteComponent(const std::string& textureID, int w, int h) :  width(w), height(h), textureID(textureID){}
	SpriteComponent(const std::string& textureID, int w, int h, float sc) : width(w), height(h), scale(sc), textureID(textureID){}
	
	std::string getTextureID() const {return textureID;}
	

	
private:
	std::string textureID;
};