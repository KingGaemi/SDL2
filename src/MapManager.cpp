#include "MapManager.h"
#include "Components/MapComponent.h"
#include <cmath>
#include "myMath.h"





void MapManager::init(){
    mapEntities.clear();
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
                // std::cout << j["tilesets"][i]["firstgid"] << std::endl;
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
            if (j["tilesets"][i].contains("tiles")) {
                // std::cout << j["tilesets"][i]["imageheight"] << std::endl;
                auto tiles = j["tilesets"][i]["tiles"];
                for(auto& tile : tiles){                    
                    PhysicalTileInfo physicaltileInfo;
                    physicaltileInfo.tileIdOrigin = tile["id"];
                    physicaltileInfo.tileId = physicaltileInfo.tileIdOrigin + tileset.firstgid;

                    auto objectgroup = tile["objectgroup"];
                    // int objectgroupId = objectgroup["id"];

                    auto objects = objectgroup["objects"];
                    for(auto& object : objects){
                        PolygonInfo poly;
                        poly.polyId = object["id"].get<int>();
                        poly.polyId += tileset.firstgid;

                        
                        if(object.contains("polygon")){
                            auto polygon = object["polygon"];
                            float offsetX = object["x"];
                            float offsetY = object["y"];
                            float rot = 0.0f;
                            if(object.contains("rotation")){
                                rot = object["rotation"];
                            }

                            for(auto vertex : polygon){
                                Vector2D vector = {vertex["x"], vertex["y"]};  
                                
                                vector.x = std::round((vector.x + offsetX) * 10) / 10;
                                vector.y = std::round((vector.y + offsetY) * 10) / 10;

                                if(rot == 90.0f) vector = rotate90(vector ,offsetX, offsetY);
                                poly.vertices.push_back(vector);
                                poly.count++;
                            }
                           
                        }else if(object.contains("height")){
                            float height = object["height"];
                            float width = object["width"];

                            float offsetX = object["x"];
                            float offsetY = object["y"];

                            Vector2D offsetVec = {offsetX, offsetY};

                            Vector2D vector1 ={0, 0};
                            Vector2D vector2 ={width, 0};
                            Vector2D vector3 ={width, height};
                            Vector2D vector4 ={0, height};

                            poly.vertices.push_back(vector1+offsetVec);
                            poly.vertices.push_back(vector2+offsetVec);
                            poly.vertices.push_back(vector3+offsetVec);
                            poly.vertices.push_back(vector4+offsetVec);
                            poly.count = 4;
                        }
                        physicaltileInfo.objects.push_back(poly);                       
                    }
                    if(!physicaltileInfo.objects.empty()){
                        physicalTiles.push_back(physicaltileInfo);
                        physicalTileBitset[physicaltileInfo.tileId] = true;
                    }
                }
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
                    int i = 1;
                    for (auto& val : dataArray) {
                        int tileId = val.get<int>(); // 정수 변환
                        mapComp->addData(layerId, tileId);
                        if(physicalTileBitset[tileId]){
                            auto it = std::find_if(physicalTiles.begin(), physicalTiles.end(), [tileId](const PhysicalTileInfo& pt) {
                                return pt.tileId == tileId;
                            });
                            PhysicalTileInfo tileInfo;
                            if (it != physicalTiles.end()) {
                                tileInfo = *it; // 찾은 객체를 복사
                                // std::cout << "Found PolygonInfo ID: " << poly.id << std::endl;
                            }


                            PendingTileInfo pendingtile;

                            int row = i / mapComp->width ;
                            int col = i % mapComp->width - 1;

                            pendingtile.x = col * mapComp->tileWidth ;
                            pendingtile.y = row * mapComp->tileHeight;
                            pendingtile.physicalTileInfo = tileInfo;

                            pendingTiles.push_back(pendingtile);
                        }
                        i++;

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

                    // float scaleMapToGame = 1.5f;

                    // x *= scaleMapToGame;
                    // y *= scaleMapToGame;
      
                    SpawnRequest req;
                    for(auto& property : obj["properties"]){
                        std::string probName = property["name"];
                        std::string probType = property["type"];
                        auto value = property["value"];
                        // std::cout << "probName: " << probName << std::endl; 
                        // std::cout << "probValue: " << value << std::endl; 

                        if(probName == "name"){
                            req.name = value;
                        }else if(probName == "entityType"){
                            if(value == "Unit") req.entityType = EntityType::Unit;
                            else if(value == "Object") req.entityType = EntityType::Object;
                            else if(value == "Wall") req.entityType = EntityType::Wall;
                            else if(value == "UI") req.entityType = EntityType::UI;
                            else if(value == "Item") req.entityType = EntityType::Item;
                        }else if(probName == "teamCode"){
                            if(value == "Ally") req.teamCode = TeamCode::Ally;
                            else if(value == "Enemy") req.teamCode = TeamCode::Enemy;
                        }
                    }
                    
                    req.x = x;
                    req.y = y;
                    req.w = w;
                    req.h = h;

                    ecsManager->pendingSpawns.push_back(req);

                }
            } else {
                std::cerr << "Failed to parse layerType." << std::endl;
            }
        }
    }
}

