#include "Systems/RenderSystem.h"
#include "Renderer.h"
#include "Groups.h"
#include "Components/PositionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/Transformcomponent.h"
#include "Components/FloatingEffectComponent.h"
#include "Components/CameraComponent.h"
#include "Components/HitboxComponent.h"
#include <iostream>
#include <algorithm>
#include "myMath.h"


SDL_FRect RenderSystem::toSDLFRect(const FRect& r) {
    SDL_FRect rect;
    rect.x = r.x;
    rect.y = r.y;
    rect.w = r.w;
    rect.h = r.h;
    return rect;
}

SDL_Rect RenderSystem::toSDLRect(const Rect& r) {
    SDL_Rect rect;
    rect.x = r.x;
    rect.y = r.y;
    rect.w = r.w;
    rect.h = r.h;
    return rect;
}




void RenderSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) {
    // 화면 클리어
    renderer->clear();

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
            // 혹은 pa->y + pa->height 등, 원하는 기준
            return pa->y < pb->y; 
        }
    );

    for (auto& entity : renderables) {
       drawEntity(entity);
    }

    renderer->display();
}




std::pair<int, int> RenderSystem::getTextureSize(const std::string& textureID){

    int width, height;
    std::cout << textureID << std::endl;
    auto texture = textureManager->getTexture(textureID); 
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    std::pair<int, int> size = {width, height};
    return size;
}


void RenderSystem::setTextureManager(TextureManager& p_textureManager){

    textureManager = &p_textureManager;
}


void RenderSystem::drawEntity(const std::shared_ptr<Entity>& entity){
    
    
    if (!entity->isActive) return;
    if(entity->hasComponent<PositionComponent>() && entity->hasComponent<SpriteComponent>()){
        auto posComp = entity->getComponent<PositionComponent>();
        auto sprite = entity->getComponent<SpriteComponent>();

        if (posComp && sprite) {

            SDL_Rect srcRect = toSDLRect(sprite->srcRect);
            SDL_FRect dstRect = toSDLFRect(sprite->dstRect);

            float offsetY = 0.0f; // for floating effect
            if(entity->hasComponent<FloatingEffectComponent>()) {
                offsetY = entity->getComponent<FloatingEffectComponent>()->renderOffsetY;
            }
            int wantIntY = static_cast<int>(offsetY);

            float worldX = posComp->x - (dstRect.w/2);
            float worldY = posComp->y + wantIntY - (dstRect.h/2);

            float screenX, screenY;
            screenX = worldX;
            screenY = worldY;

            cameraEntity = ecsManager->getCamera();
            if(cameraEntity->isActive){
                auto cameraPos = cameraEntity->getComponent<PositionComponent>();
                if(cameraPos){
                   screenX = worldX - cameraPos->x;
                   screenY = worldY - cameraPos->y;
                }
            }

            dstRect.x = screenX;
            dstRect.y = screenY;

            SDL_RendererFlip flip = SDL_FLIP_NONE;
            float rot = 0.0f;
            
            if (sprite->flipHorizontal) flip = SDL_FLIP_HORIZONTAL;
            if (sprite->flipVertical) flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
            
            if (entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                rot = transComp->rotation;
            }

            auto texture = textureManager->getTexture(sprite->getTextureID());
            renderer->render(texture, &srcRect, &dstRect, rot, nullptr, flip);
        }
    }


    if(debugMode){
        if (entity->hasComponent<HitboxComponent>()) {
            auto hitboxComp = entity->getComponent<HitboxComponent>();
            auto posComp = entity->getComponent<PositionComponent>();
            // collider 위치(월드 좌표) -> 화면 좌표 변환
            // (camX, camY) 만큼 빼주기, 혹은 camTransform 적용
            float worldX = posComp->x;
            float worldY = posComp->y;

            float screenX, screenY;
            screenX = worldX;
            screenY = worldY;
            if(cameraEntity){
                auto cameraPos = cameraEntity->getComponent<PositionComponent>();
                if(cameraPos){
                   screenX = worldX - cameraPos->x;                   
                   screenY = worldY - cameraPos->y;
                }
            }

            SDL_FRect debugRect;
            debugRect.x = screenX;
            debugRect.y = screenY;
            debugRect.w = hitboxComp->w;
            debugRect.h = hitboxComp->h;

            float rot = 0.0f;
            if (entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                rot = transComp->rotation;
            }
            
            renderer->SetRenderDrawColor(255, 0, 0, 255);
            renderer->RenderDrawRect(debugRect, rot);

        }
    }
}

