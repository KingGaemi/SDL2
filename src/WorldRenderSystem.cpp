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

                                int tileID;
                                if(index < static_cast<int>(layer.tileData.size())) tileID = layer.tileData[index++];
                                if (tileID == 0) {
                                    continue; // 빈 타일이므로 그리지 않음
                                }

                                // (예) 256x256 이미지에 16x16 타일이면 16칸
                                int adjustedID = tileID - tilesetInfo.firstgid;  // firstgid=1 이면 1 빼주기
                                // 
                                if(adjustedID <= 0) continue;

                                int srcX = (adjustedID % tilesPerRow) * mapComp->tileWidth;
                                int srcY = (adjustedID / tilesPerRow) * mapComp->tileHeight;

                                // 화면(또는 월드)에서 그려질 위치

                                float dstX = col * mapComp->tileWidth;
                                float dstY = row * mapComp->tileHeight;
                                if(cameraEntity){
                                    auto cameraPoscomp = cameraEntity->getComponent<PositionComponent>();
                                    dstX -= cameraPoscomp->x/2;
                                    dstY -= cameraPoscomp->y/2;
                                }
                                // 실제 SDL draw 호출 (pseudo)
                                SDL_Rect srcRect = { srcX, srcY, mapComp->tileWidth,mapComp->tileHeight };
                                SDL_FRect dstRect = { dstX*2, dstY*2, static_cast<float>(mapComp->tileWidth*2), static_cast<float>(mapComp->tileHeight*2) };                    
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


        std::vector<std::shared_ptr <Entity>> renderables;
        for (auto& e : entities) {
            if (e->hasComponent<PositionComponent>() && e->hasComponent<SpriteComponent>()) {
                renderables.push_back(e);
            }
        }

        // 2) 정렬 (y 좌표 기준 오름차순)
        std::sort(renderables.begin(), renderables.end(), 
            [](std::shared_ptr <Entity> a, std::shared_ptr <Entity> b){
                auto pa = a->getComponent<PositionComponent>();
                auto pb = b->getComponent<PositionComponent>();
                auto sa = a->getComponent<SpriteComponent>();
                auto sb = b->getComponent<SpriteComponent>();
                

                float offsetA = sa->dstRect.h/2;
                float offsetB = sb->dstRect.h/2;
                if(a->hasComponent<HitboxComponent>()){
                    auto hitComp = a->getComponent<HitboxComponent>();
                    offsetA = hitComp->w/2 + hitComp->offsetY;
                }
                if(b->hasComponent<HitboxComponent>()){
                    auto hitComp = b->getComponent<HitboxComponent>();
                    offsetB = hitComp->w/2 + hitComp->offsetY;
                }
                return pa->y + offsetA < pb->y + offsetB;
            }
        );


        for (auto& entity : renderables) {
            if (entity->hasComponent<UITag>()) continue;
            drawEntity(entity);
        }


    }