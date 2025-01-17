#include "Systems/MapSystem.h"
#include "Components/ColliderComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/PositionComponent.h"
#include <iostream>

void MapSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime){
	renderer->clear(); 
	if(!mapEntity) return;
	if(!mapComp) return;
	int index = 0;

    if(!mapComp->layerMap.empty()){
        for(const auto& pair: mapComp->layerMap){
            const std::string& layerName = pair.first;
            const LayerInfo& layerInfo = pair.second;

            for (int row = 0; row < mapComp->height; row++) {
                for (int col = 0; col <  mapComp->width; col++) {
                    // tileID 읽기 (0이면 타일 없음)
                   
                    // std::cout << layerInfo.tileData.size() << std::endl;
                    // std::cout << mapComp->width * mapComp->height << std::endl;
                    // if(layerInfo.tileData.size() <  mapComp->width * mapComp->height) continue;
                    int tileID = layerInfo.tileData[index++];
                    if (tileID == 0) {
                        continue; // 빈 타일이므로 그리지 않음
                    }
                       // std::cout << "Check" << std::endl;    
                    // tileID 에 맞는 'source rectangle' 계산
                    // 예: 한 줄에 8개씩 배치된 타일셋이라면
                    //     srcX = (tileID % 8) * tW
                    //     srcY = (tileID / 8) * tH
                    // 실제 계산은 타일셋의 구조(tileset.width / tileWidth) 등에 따라 달라짐
                    // Tiled에서 firstgid가 있으면, tileID -= firstgid-1 등 보정이 필요할 수도 있음

                    int tilesPerRow = 16; // (예) 256x256 이미지에 16x16 타일이면 16칸
                    int adjustedID = tileID - layerInfo.firstGid;  // firstgid=1 이면 1 빼주기
                    int srcX = (adjustedID % tilesPerRow) * mapComp->tileWidth;
                    int srcY = (adjustedID / tilesPerRow) * mapComp->tileHeight;

                    // 화면(또는 월드)에서 그려질 위치
                    int dstX = col * mapComp->tileWidth;
                    int dstY = row * mapComp->tileHeight;
                    // 실제 SDL draw 호출 (pseudo)

                    SDL_Rect srcRect = { srcX, srcY, mapComp->tileWidth, mapComp->tileHeight };
                    SDL_Rect dstRect = { dstX*2, dstY*2, mapComp->tileWidth*2, mapComp->tileHeight*2 };

                    std::cout << layerInfo.textureID << std::endl;
                    auto texture = textureManager->getTexture(layerInfo.textureID);
                    renderer->render(texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
                }
            }
        }
    }
	// auto texture = textureManager->getTexture(mapComp->textureID);
	// SDL_Rect srcRect = { 0, 0, 1600, 1000 };
	// SDL_Rect dstRect = { 0, 0, 1600, 1000 };
    // renderer->render(texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}



void MapSystem::init(std::vector<std::shared_ptr<Entity>>& entities){

	json j = json::parse(std::ifstream("map/test_ground.tmj"));
	mapEntity = ecsManager->createEntity();
	mapEntity->addComponent<MapComponent>("base");
    mapComp = mapEntity->getComponent<MapComponent>();
    mapComp->addLayer("ground", "grass_tileset", 1);
    mapComp->addLayer("props", "props_tileset", 257);

	ecsManager->setMapEntity(mapEntity);
    
    // auto& layerInfo = mapComp->layerMap["props"];
    // layerInfo.firstGid = 257;

	if(mapComp){
		mapComp->width = j["width"];
		mapComp->height = j["height"];
		mapComp->tileWidth = j["tilewidth"];
		mapComp->tileHeight = j["tileheight"];
		// mapWidth = mapComp->width;
		// mapHeight = mapComp->height;
		// tileWidth = mapComp->tileWidth;
		// tileHeight = mapComp->tileHeight;

		for (auto layerJson: j["layers"]) {
		    std::string layerType = layerJson.value("type", "");
		    if (layerType == "tilelayer") {
		        parseTileLayer(layerJson);
		    } else if (layerType == "objectgroup") {
		        parseObjectLayer(layerJson);
		    } else {
		    	std::cerr << "Failed to parse layerType." << std::endl;
		    }
	    }
	}
}


void MapSystem::parseTileLayer(const json& layerJson) {
    // layerJson["data"]는 배열 형태의 tile ID 목록
    std::string layerName = layerJson["name"];
	if (layerJson.contains("data") && layerJson["data"].is_array()) {
	    auto dataArray = layerJson["data"];
        // std::cout <<layerName <<std::endl;
	    for (auto& val : dataArray) {
	        int tileID = val.get<int>(); // 정수 변환
            mapComp->addData(layerName, tileID);
	    }        
	}

    // int row = layerJson["width"];
    // int col = layerJson["height"];

    // // 레이어 크기는 layerJson["width"], layerJson["height"] 또는 상위 맵의 width, height로 판단
    // // Tiled 설정에 따라 다를 수 있음
    // // 예: 60 x 100
    // // dataArray는 크기가 width*height
    // int index = 0;
    // for (auto& tileId : dataArray) {

    //     // tileId = 1025, 1026, ... (0이면 타일 없음)
    //     // row, col 계산
    //     // ex) row = index / layerWidth, col = index % layerWidth
    //     // 타일맵에 저장하기
    //     index++;
    // }
}



void MapSystem::parseObjectLayer(const json& layerJson) {
    auto objects = layerJson["objects"];
    for (auto& obj : objects) {
        // obj["x"], obj["y"], obj["width"], obj["height"], obj["name"], ...
        std::string name = obj.value("name", "");
        float x = obj.value("x", 0.0f);
        float y = obj.value("y", 0.0f);
        float w = obj.value("width", 0.0f);
        float h = obj.value("height", 0.0f);

        auto object = ecsManager->createEntity();
        object->addComponent<PositionComponent>(x, y);
        object->addComponent<ColliderComponent>(w, h, 2.0f, ColliderType::Object);
        object->addComponent<PhysicsComponent>(BodyType::Static);
        // ECS 엔티티 생성해서 ColliderComponent 등 붙이거나,
        // 맵상에 특정 구역으로 저장
        // if (name == "dead_zone") {...} etc.
    }
}

