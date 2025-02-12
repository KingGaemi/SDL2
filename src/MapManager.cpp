#include "MapManager.h"
#include "Components/MapComponent.h"





void MapManager::init(){
    auto mapEntity = ecsManager->createEntity();
    mapEntity->addComponent<MapComponent>("home_map");
    mapEntities.push_back(mapEntity);
   

}


void MapManager::loadMap(const std::string& mapPath){
    nlohmann::json j = json::parse(std::ifstream(mapPath));
    for(auto& mapEntity: mapEntities){
        if(!mapEntity) {
            std::cout << "mapEntity is nullptr" << std::endl;
            continue;
        }       
        auto mapComp = mapEntity->getComponent<MapComponent>();
        mapComp->width = j["width"];
        mapComp->height = j["height"];
        mapComp->tileWidth = j["tilewidth"];
        mapComp->tileHeight = j["tileheight"];
        
        for( int i = 0 ; i <  static_cast<int>(j["tilesets"].size()) ; i ++){
            TilesetInfo tileset;
            // set firstgid
            if (j["tilesets"][i].contains("firstgid")) {
                std::cout << j["tilesets"][i]["firstgid"] << std::endl;
                tileset.firstgid = j["tilesets"][i]["firstgid"];
            }

            // load tileset texture and set textureId, path
            if (j["tilesets"][i].contains("image")) {      
                std::string textureId = j["tilesets"][i]["image"];
                std::string tilePath = j["tilesets"][i]["image"];
                if (textureId.size() > 4) {
                    textureId.resize(textureId.size() - 4);
                } else {
                    textureId.clear(); // 문자열 길이보다 큰 경우 빈 문자열로 만듦
                }
                tilePath = "maps/" + tilePath;
                std::cout << "before to load texture" << std::endl << tilePath << " " << textureId << std::endl;


                if(textureManager->loadTexture(textureId, tilePath)){
                    // std::cout << "before to load texture" << std::endl;
                    tileset.imagePath = tilePath;
                    tileset.textureId = textureId;
                    tileset.tilesetName = textureId;
                    // std::cout << tileset.imagePath << ", " << tileset.textureId << std::endl;
                }else{
                    std::cout << "failed to load tileset texture" << std::endl;
                }

            }

            // set tilecount, imagewidth, height
            if (j["tilesets"][i].contains("tilecount")) {
                // std::cout << j["tilesets"][i]["tilecount"] << std::endl;
                tileset.tilecount = j["tilesets"][i]["tilecount"];
            }
            if (j["tilesets"][i].contains("imagewidth")) {
                // std::cout << j["tilesets"][i]["imagewidth"] << std::endl;
                tileset.imagewidth = j["tilesets"][i]["imagewidth"];
            }
            if (j["tilesets"][i].contains("imageheight")) {
                // std::cout << j["tilesets"][i]["imageheight"] << std::endl;
                tileset.imageheight = j["tilesets"][i]["imageheight"];
            }

            mapComp->addTileset(tileset);
        }



        for( int i = 0 ; i <  static_cast<int>(j["layers"].size()) ; i ++){
            // j["layers"][i] = layer
            LayerInfo layer;
            layer.layerName = j["layers"][i]["name"];
            layer.layerType = LayerType::tilelayer;
            if(j["layers"][i]["type"] == "objectgroup") layer.layerType = LayerType::objectgroup;
            layer.layerId = j["layers"][i]["id"];
            mapComp->addLayer(layer);
        }
        
        
        for (auto layerJson: j["layers"]) {

            std::string layerType = layerJson.value("type", "");
            if (layerType == "tilelayer") {
                int layerId = layerJson["id"];
                if (layerJson.contains("data") && layerJson["data"].is_array()) {
                    auto dataArray = layerJson["data"];
                    // std::cout << layerName <<std::endl;
                    for (auto& val : dataArray) {
                        int tileID = val.get<int>(); // 정수 변환
                        mapComp->addData(layerId, tileID);
                    }        
                }
            } else if (layerType == "objectgroup") {
                auto objects = layerJson["objects"];
                for (auto& obj : objects) {
                    // obj["x"], obj["y"], obj["width"], obj["height"], obj["name"], ...
                    std::string name = obj.value("name", "");
                    float x = obj.value("x", 0.0f);
                    float y = obj.value("y", 0.0f);
                    float w = obj.value("width", 0.0f);
                    float h = obj.value("height", 0.0f);

                    float scaleMapToGame = 1.5f;

                    x *= scaleMapToGame;
                    y *= scaleMapToGame;
      

                    SpawnRequest req;
                    for(auto& property : obj["properties"]){
                        std::string probName = property["name"];
                        std::string probType = property["type"];
                        auto value = property["value"];
                        // std::cout << "probName: " << probName << std::endl; 

                        if(probName == "name"){
                            req.name = value;
                        }else if(probName == "entityType"){
                            if(value == "Unit") req.entityType = EntityType::Unit;
                            else if(value == "Object") req.entityType = EntityType::Object;
                            else if(value == "Wall") req.entityType = EntityType::Wall;
                        }else if(probName == "teamCode"){
                            if(value == "Ally") req.teamCode = TeamCode::Ally;
                            else if(value == "Enemy") req.teamCode = TeamCode::Enemy;
                        }
                    }
                    // req.name = "stone";
                    req.x = x;
                    req.y = y;
                    req.w = w;
                    req.h = h;
                    // req.sc = 2.0f;
                    // std::cout << "objectgroup" << std::endl;
                    ecsManager->pendingSpawns.push_back(req);

                }
            } else {
                std::cerr << "Failed to parse layerType." << std::endl;
            }
        }
    }
}


// void MapManager::parseTileLayer(const json& layerJson) {
//     // layerJson["data"]는 배열 형태의 tile ID 목록
//     std::string layerName = layerJson["name"];
// 	if (layerJson.contains("data") && layerJson["data"].is_array()) {
// 	    auto dataArray = layerJson["data"];
//         // std::cout <<layerName <<std::endl;
// 	    for (auto& val : dataArray) {
// 	        int tileID = val.get<int>(); // 정수 변환
//             mapComp->addData(layerName, tileID);
// 	    }        
// 	}
// }

// void MapManager::parseObjectLayer(const json& layerJson) {
//     auto objects = layerJson["objects"];
//     for (auto& obj : objects) {
//         // obj["x"], obj["y"], obj["width"], obj["height"], obj["name"], ...
//         std::string name = obj.value("name", "");
//         float x = obj.value("x", 0.0f);
//         float y = obj.value("y", 0.0f);
//         float w = obj.value("width", 0.0f);
//         float h = obj.value("height", 0.0f);

//         SpawnRequest req;

//         req.entityType = EntityType::Props;
//         // req.name = "stone";
//         req.x = x;
//         req.y = y;
//         req.w = w;
//         req.h = h;
//         req.sc = 2.0f;
//         ecsManager->pendingSpawns.push_back(req);

//     }
// }

