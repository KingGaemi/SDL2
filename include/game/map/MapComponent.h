#pragma once
#include "engine/ecs/core/Component.h"

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

enum class LayerType{
	tilelayer,
	objectgroup
};


struct LayerInfo{
	std::string layerName;
	LayerType layerType;
	// std::pair<int, int> textureResolution;
	std::vector<int> tileData;
	int layerId = 0;
};

struct TilesetInfo{
	std::string tilesetName;
	std::string imagePath;
	std::string textureId;
	int firstgid = 0;
	int tilecount;
	int imageheight;
	int imagewidth;
	int margin;
	float hasTiles;
	// std::vector<std::unordered_map<int, std::vector<Vector2D>>> tilesPolygon;
};



class MapComponent : public Component{

public:
	std::string mapName;
    int width = 0, height = 0;
    int tileWidth = 0, tileHeight = 0;


	MapComponent(const std::string& mapName) : mapName(mapName) {}

	void addLayer(const LayerInfo& layer){
		layers.push_back(layer);
	}

	void addTileset(const TilesetInfo& tileset){
		tilesetMap.insert({tileset.tilesetName, tileset});
	}

	void addData(int layerId, int data) {
		for(auto& layer : layers){
			if(layer.layerId == layerId) layer.tileData.push_back(data);
		}
	}


	std::vector<LayerInfo> layers;  // layerName, layerInfo
	std::unordered_map<std::string, TilesetInfo> tilesetMap;

};