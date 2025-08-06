#pragma once

#include "nlohmann/json.hpp"
#include "engine/math/Vector2D.h"

using json = nlohmann::json;

struct PolygonInfo{
	int polyId;
	Vector2D pos;
	std::vector<Vector2D> vertices;
	int32_t count = 0;
};


enum class ObjectType{
    polygon,
  	  
};

struct PhysicalTileInfo{
	int tileId;
	int tileIdOrigin;
	std::vector<PolygonInfo> objects;
};

struct PendingTileInfo{
	float x, y;
	PhysicalTileInfo physicalTileInfo;
};

struct CollisionObject{
    int objectId;
    ObjectType objectType;
    std::vector<Vector2D> vertices;
};

class MapManager{


public:
	MapManager() : () {}
	void init();
	void loadMap(const std::string& mapPath);
	void parseTileLayer(const json& layerJson);
	void parseObjectLayer(const json& layerJson);
    void setTextureManager(TextureManager& p_textureManager) {
    	 textureManager = &p_textureManager;
    } 

    bool enterMap;
	std::vector<PendingTileInfo> pendingTiles;
private:
	TextureManager* textureManager;
	std::vector<PhysicalTileInfo> physicalTiles;
	std::vector<std::shared_ptr<Entity>> mapEntities;
	std::shared_ptr<ECSManager> ecsManager;
	std::bitset<999999> physicalTileBitset;
};