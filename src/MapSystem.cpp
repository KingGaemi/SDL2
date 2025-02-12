#include "Systems/MapSystem.h"
#include "Components/ColliderComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/PositionComponent.h"
#include "Components/CameraComponent.h"

#include <iostream>


// void MapSystem::init(){

//     json j = json::parse(std::ifstream("map/test3.tmj"));
//     mapEntity = ecsManager->createEntity();
//     mapEntity->addComponent<MapComponent>("base");
//     mapComp = mapEntity->getComponent<MapComponent>();
//     mapComp->addLayer("props", "props_tileset", 1);
//     mapComp->addLayer("ground", "grass_tileset", 1025);

    
//     // ecsManager->setMapEntity(mapEntity);

//     if(mapComp){
//         mapComp->width = j["width"];
//         mapComp->height = j["height"];
//         mapComp->tileWidth = j["tilewidth"];
//         mapComp->tileHeight = j["tileheight"];

//         for (auto layerJson: j["layers"]) {
//             std::string layerType = layerJson.value("type", "");
//             if (layerType == "tilelayer") {
//                 parseTileLayer(layerJson);
//             } else if (layerType == "objectgroup") {
//                 parseObjectLayer(layerJson);
//             } else {
//                 std::cerr << "Failed to parse layerType." << std::endl;
//             }
//         }
//     }
// }

// void MapSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
// 	renderer->clear(); 
//     cameraEntity = ecsManager->getEntityByName("camera");
// 	if(!mapEntity) return;
//     if(!mapEntity->isActive) return;
// 	if(!mapComp) return;
//     if(!mapComp->layerMap.empty()){
//         for(const auto& pair: mapComp->layerMap){
//             // const std::string& layerName = pair.first;
//             const LayerInfo& layerInfo = pair.second;
//             auto texture = textureManager->getTexture(layerInfo.textureID);
//             auto resolution = textureManager->getTextureResolution(layerInfo.textureID);
//             int tilesPerRow = resolution.first / mapComp->tileWidth ;
//             int index = 0;
//             for (int row = 0; row < mapComp->height; row++) {
//                 for (int col = 0; col <  mapComp->  width; col++) {

//                     int tileID = layerInfo.tileData[index++];
//                     if (tileID == 0) {
//                         continue; // 빈 타일이므로 그리지 않음
//                     }

//                     // (예) 256x256 이미지에 16x16 타일이면 16칸
//                     int adjustedID = tileID - layerInfo.firstGid;  // firstgid=1 이면 1 빼주기
//                     int srcX = (adjustedID % tilesPerRow) * mapComp->tileWidth;
//                     int srcY = (adjustedID / tilesPerRow) * mapComp->tileHeight;

//                     // 화면(또는 월드)에서 그려질 위치

//                     float dstX = col * mapComp->tileWidth;
//                     float dstY = row * mapComp->tileHeight;
//                     if(cameraEntity){
//                         auto cameraPoscomp = cameraEntity->getComponent<PositionComponent>();
//                         dstX -= cameraPoscomp->x/2;
//                         dstY -= cameraPoscomp->y/2;
//                     }
//                     // 실제 SDL draw 호출 (pseudo)


//                     SDL_Rect srcRect = { srcX, srcY, mapComp->tileWidth,mapComp->tileHeight };
//                     SDL_FRect dstRect = { dstX*2, dstY*2, static_cast<float>(mapComp->tileWidth*2), static_cast<float>(mapComp->tileHeight*2) };                    
//                     renderer->render(texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
//                 }
//             }
//         }
//     }
//     // auto texture = textureManager->getTexture("props_tileset");
//     // SDL_Rect srcRect = { 0, 0, 1000, 1000 };
//     // SDL_Rect dstRect = { 0, 0, 1000, 1000 };                    
//     // renderer->render(texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
// }




// void MapSystem::parseTileLayer(const json& layerJson) {
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



// void MapSystem::parseObjectLayer(const json& layerJson) {
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
//         // auto object = ecsManager->createEntity();
//         // object->addComponent<PositionComponent>(x*2, y*2);
//         // object->addComponent<ColliderComponent>(w*2, h*2, 2.0f, ColliderType::Object);
//         // object->addComponent<TransformComponent>(w*2, h*2, 2.0f);
//         // object->addComponent<PhysicsComponent>(BodyType::Static);
//         // object->addComponent<SceneTag>(SceneCode::Game);
//         // // object->isActive = false;
//     }
// }

