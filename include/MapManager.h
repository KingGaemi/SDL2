#pragma once

#include "TextureManager.h"
#include "Components/MapComponent.h"
#include "Systems/MapSystem.h"
#include "nlohmann/json.hpp"

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
	std::shared_ptr<ECSManager> ecsManager;
};