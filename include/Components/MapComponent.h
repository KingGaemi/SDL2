#pragma once
#include "ECS/Component.h"



class MapComponent : public Component{

public:
	int width, height;
	int tileWidth, tileHeight;


	MapComponent(const std::string& texID) : textureID(texID){}

	std::vector<int> tileData;

	
	std::string textureID;

};