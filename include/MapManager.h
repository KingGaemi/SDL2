#pragma once

#include "TextureManager.h"
#include "Components/MapComponent.h"
#include "ECS/ECSManager.h"
#include "nlohmann/json.hpp"
#include "Vector2D.h"





enum class ObjectType{
    polygon,
  	  
};

struct collisionObject{
    int objectId;
    ObjectType objectType;
    std::vector<Vector2D> vertices;
};

class MapManager{


public:
	MapManager(std::shared_ptr<ECSManager> ecsManager) : ecsManager(ecsManager) {}
	void init();
	void loadMap(const std::string& mapPath);
	void parseTileLayer(const json& layerJson);
	void parseObjectLayer(const json& layerJson);
    void setTextureManager(TextureManager& p_textureManager) {
    	 textureManager = &p_textureManager;
    } 


private:
	TextureManager* textureManager;
	std::vector<std::shared_ptr<Entity>> mapEntities;
	// std::queue<polygonInfo> polygons;
	std::shared_ptr<ECSManager> ecsManager;
};