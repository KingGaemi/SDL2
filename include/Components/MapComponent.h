#pragma once
#include "ECS/Component.h"
#include <iostream>


struct LayerInfo{
	std::string layerName;
	std::string textureID;
	std::vector<int> tileData;
	int firstGid = 1;
};


class MapComponent : public Component{

public:
	std::string mapName;
    int width = 0, height = 0;
    int tileWidth = 0, tileHeight = 0;


	MapComponent(const std::string& mapName) : mapName(mapName) {}

	void addLayer(const std::string& layerName, const std::string& texID, int firstGid){
		LayerInfo layer;
		layer.layerName = layerName;
		layer.textureID = texID;
		layer.firstGid = firstGid;
		layerMap.insert({layerName, layer});
	}

	void addData(const std::string& layerName, int data){
		for(auto& pair : layerMap){
			if(pair.first == layerName){
				auto layerInfo = pair.second;
				layerInfo.tileData.push_back(data);
			}
		}
	}

	
	
	std::unordered_map<std::string, LayerInfo> layerMap;  // layerName, layerInfo


};