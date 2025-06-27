#include "Systems/WorldRenderSystem.h"



void WorldRenderSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) {
    renderer->clear(); 

    std::shared_ptr <Entity> currentMap;
    for (auto& e : entities) {
        if (e->hasComponent<MapComponent>() && e->isActive) {
            currentMap = e;
            continue;
        }
    }

    renderMap(currentMap);
    RenderSystem::update(entities, deltaTime);
    

}

void WorldRenderSystem::renderMap(std::shared_ptr<Entity>& currentMap){
    if(currentMap){
        auto mapComp = currentMap->getComponent<MapComponent>();
        if(!mapComp->layers.empty()){
            for(const auto& layer: mapComp->layers){

                if(mapComp->tilesetMap.empty()) continue;
                for(const auto& pair: mapComp->tilesetMap){                       
                    const TilesetInfo& tilesetInfo = pair.second;

                    auto texture = textureManager->getTexture(tilesetInfo.textureId);
                    int imagewidth = tilesetInfo.imagewidth;
                    // int imageheight = tilesetInfo.imageheight;
                    int tilesPerRow = imagewidth / mapComp->tileWidth;

                    int index = 0;
                    for (int row = 0; row < mapComp->height; row++) {
                        for (int col = 0; col < mapComp->width; col++) {

                            int tileID = 0;
                            if(index < static_cast<int>(layer.tileData.size())) tileID = layer.tileData[index++];
                            if(tileID == 0) continue; // 빈 타일이므로 그리지 않음
                          

                            // (예) 256x256 이미지에 16x16 타일이면 16칸
                            int adjustedID = tileID - tilesetInfo.firstgid;  // firstgid=1 이면 1 빼주기
                            // 
                            if(adjustedID < 0) continue;

                            int srcX = (adjustedID % tilesPerRow) * mapComp->tileWidth;
                            int srcY = (adjustedID / tilesPerRow) * mapComp->tileHeight;

                            // 화면(또는 월드)에서 그려질 위치

                            float dstX = col * mapComp->tileWidth;
                            float dstY = row * mapComp->tileHeight;

                            if(cameraEntity&&cameraEntity->isActive){
                                auto cameraPos = cameraEntity->getComponent<PositionComponent>();
                                if(cameraPos){
                                   dstX = dstX - cameraPos->x;
                                   dstY = dstY - cameraPos->y;
                                }
                            }
                            // 실제 SDL draw 호출 (pseudo)
                            SDL_Rect srcRect = { srcX, srcY, mapComp->tileWidth,mapComp->tileHeight };
                            SDL_FRect dstRect = { dstX, dstY, static_cast<float>(mapComp->tileWidth), static_cast<float>(mapComp->tileHeight) };                    
                            renderer->render(texture, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
                        }
                    }
                }
            }
        }
    }else{

        std::cout << "There is no activated map" << std::endl;
    }
    // auto mapComp = currentMap->getComponent<MapComponent>();

}
