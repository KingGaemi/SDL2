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
#include "Components/ClickableComponent.h"
#include "Components/TextLabelComponent.h"
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
    cameraEntity = ecsManager->getCamera();
    std::vector<std::shared_ptr <Entity>> renderables;
    std::vector<std::shared_ptr <Entity>> shadows;
    std::vector<std::shared_ptr <Entity>> texts;
    for (auto& e : entities) {
        if (e->hasComponent<PositionComponent>() && e->hasComponent<SpriteComponent>()) {
            renderables.push_back(e);
        }
        if (e->hasComponent<PositionComponent>() && e->hasComponent<SpriteComponent>() && e->hasComponent<ShadowComponent>()) {
            shadows.push_back(e);
        }
        if (e->hasComponent<PositionComponent>() && e->hasComponent<TextLabelComponent>()){
            texts.push_back(e);
        }
    }

     // **Z-Index 먼저 정렬 → 같은 Z에서 Y 오름차순 정렬**
    auto sortFn = [](std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
        auto sa = a->getComponent<SpriteComponent>();
        auto sb = b->getComponent<SpriteComponent>();

        if (sa->zIndex != sb->zIndex) {
            return sa->zIndex < sb->zIndex; // **Z-Index 낮은 것 먼저**
        }

        auto pa = a->getComponent<PositionComponent>();
        auto pb = b->getComponent<PositionComponent>();
        return pa->y < pb->y; // **같은 Z일 때는 Y 작은 것 먼저**
    };

    std::sort(renderables.begin(), renderables.end(), sortFn);
    std::sort(shadows.begin(), shadows.end(), sortFn);

    // // 2) 정렬 (y 좌표 기준 오름차순)
    // std::sort(renderables.begin(), renderables.end(), 
    //     [](std::shared_ptr <Entity> a, std::shared_ptr <Entity> b){
    //         auto pa = a->getComponent<PositionComponent>();
    //         auto pb = b->getComponent<PositionComponent>();
    //         // 혹은 pa->y + pa->height 등, 원하는 기준
    //         return pa->y < pb->y; 
    //     }
    // );

    // std::sort(shadows.begin(), shadows.end(), 
    //     [](std::shared_ptr <Entity> a, std::shared_ptr <Entity> b){
    //         auto pa = a->getComponent<PositionComponent>();
    //         auto pb = b->getComponent<PositionComponent>();
    //         // 혹은 pa->y + pa->height 등, 원하는 기준
    //         return pa->y < pb->y; 
    //     }
    // );

    for (auto& entity : shadows) {
       drawShadow(entity);
    }
    for (auto& entity : renderables) {
       drawEntity(entity);
    }
    for (auto& entity : texts) {
       drawText(entity);

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
    
    
    if (!entity->isActive || !entity->isVisible) return;
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

            float worldX = posComp->x - (dstRect.w/2.0f) + sprite->offsetX;
            float worldY = posComp->y + wantIntY - (dstRect.h/2.0f) + sprite->offsetY;

            float screenX, screenY;
            screenX = worldX;
            screenY = worldY;
            
            if(cameraEntity && cameraEntity->isActive){
                auto cameraPos = cameraEntity->getComponent<PositionComponent>();
                if(cameraPos && (!entity->hasComponent<UITag>()|| (entity->hasComponent<UITag>() && entity->hasComponent<HpBarTag>()))){
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
                rot = toAngle(transComp->radian);
            }

            auto texture = textureManager->getTexture(sprite->getTextureId());
            if(!texture){
                texture = textureManager->unknown;
                sprite->textureId = "unknown";
            }
            renderer->render(texture, &srcRect, &dstRect, rot, nullptr, flip);
        }
    }

    if(debugMode){
        if (entity->hasComponent<HitboxComponent>()) {
            auto hitboxComp = entity->getComponent<HitboxComponent>();
            auto posComp = entity->getComponent<PositionComponent>();
            auto spriteComp = entity->getComponent<SpriteComponent>();


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
            if(false){
                if(!spriteComp) return;
                debugRect.w = spriteComp->dstRect.w;
                debugRect.h = spriteComp->dstRect.h;
            }else{
                debugRect.w = hitboxComp->w;
                debugRect.h = hitboxComp->h;
            }

            float rad = 0.0f;
            if (entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                rad = transComp->radian;
            }
            
            renderer->SetRenderDrawColor(255, 0, 0, 255);
            renderer->RenderDrawRect(debugRect, rad);

        }
        if(entity->hasComponent<ClickableComponent>() && entity->hasComponent<PositionComponent>()){

            auto clickComp = entity->getComponent<ClickableComponent>();
            auto posComp = entity->getComponent<PositionComponent>();
            SDL_FRect debugRect;
            debugRect = { debugRect.x = posComp->x,
                    debugRect.y = posComp->y,
                    debugRect.w = clickComp->rect.w,
                    debugRect.h = clickComp->rect.h
            };
            renderer->SetRenderDrawColor(255, 0, 0, 255);
            renderer->RenderDrawRect(debugRect, 0);
        }
    }

}


void RenderSystem::drawShadow(const std::shared_ptr<Entity>& entity){
    
    
    if (!entity->isActive || !entity->isVisible) return;
    if(!entity->hasComponent<PositionComponent>() ||
       !entity->hasComponent<SpriteComponent>()   ||
       !entity->hasComponent<ShadowComponent>()) return;



    auto pos = entity->getComponent<PositionComponent>();
    auto sprite = entity->getComponent<SpriteComponent>();
    auto shadow = entity->getComponent<ShadowComponent>();


    if(!pos || !sprite || !shadow) return;
    
    SDL_Rect srcRect = toSDLRect(shadow->srcRect);
    SDL_FRect dstRect = toSDLFRect(shadow->dstRect);

    float worldX = pos->x - (dstRect.w/2.0f) + shadow->offsetX;
    float worldY = pos->y - (dstRect.h/2.0f) + shadow->offsetY;

    float screenX = worldX;
    float screenY = worldY;

    if(cameraEntity && cameraEntity->isActive){
        auto cameraPos = cameraEntity->getComponent<PositionComponent>();
        if(cameraPos && !entity->hasComponent<UITag>()){
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
        rot = toAngle(transComp->radian);
    }

    std::string textureId = sprite->getTextureId();
    std::string shadowTextureId = textureId + "-shadow";
    auto texture = textureManager->getTexture(shadowTextureId);
    if(!texture){
        texture = textureManager->unknown;
        sprite->textureId = "unknown";
    }
    renderer->render(texture, &srcRect, &dstRect, rot, nullptr, flip);

}


void RenderSystem::drawEffects(){

    for(auto& effectRequest : effectManager->pendingEffects){

        std::string textureId = effectRequest.textureId;
        SDL_Rect srcRect = toSDLRect(effectRequest.srcRect);
        SDL_FRect dstRect = toSDLFRect(effectRequest.dstRect);
        float rot = effectRequest.rot;



        if(cameraEntity){
            auto cameraPos = cameraEntity->getComponent<PositionComponent>();
            if(cameraPos){
               dstRect.x = dstRect.x - cameraPos->x;                   
               dstRect.y = dstRect.y - cameraPos->y;
            }
        }

        //temp
        if(textureId == "black"){
            renderer->SetRenderDrawColor(0, 0, 0, 0);
            renderer->RenderFillRectF(&dstRect);
        }else if(textureId == "damageText"){            
            textureManager->loadText(std::to_string(effectRequest.textNumber).c_str());
            auto texture = textureManager->getTexture(std::to_string(effectRequest.textNumber).c_str());
            renderer->render(texture, nullptr, &dstRect, rot, nullptr, SDL_FLIP_NONE);
    
            
            // std::cout <<"render text" << std::endl;
        }else{
            
            auto texture = textureManager->getTexture(textureId);

            if(!texture){
                texture = textureManager->unknown;            
            }
            renderer->render(texture, &srcRect, &dstRect, rot, nullptr, SDL_FLIP_NONE);
        }
    }

    effectManager->pendingEffects.clear();

}

void RenderSystem::drawUI(const std::shared_ptr<Entity>& entity){
    
    if (!entity->isActive) return;
    if(entity->hasComponent<PositionComponent>() && entity->hasComponent<SpriteComponent>()){
        auto posComp = entity->getComponent<PositionComponent>();
        auto sprite = entity->getComponent<SpriteComponent>();

        if (posComp && sprite) {

            SDL_Rect srcRect = toSDLRect(sprite->srcRect);
            SDL_FRect dstRect = toSDLFRect(sprite->dstRect);


            dstRect.x = posComp->x - (dstRect.w/2) + sprite->offsetX;
            dstRect.y = posComp->y - (dstRect.h/2) + sprite->offsetY;

            SDL_RendererFlip flip = SDL_FLIP_NONE;
            float rot = 0.0f;
            
            if (sprite->flipHorizontal) flip = SDL_FLIP_HORIZONTAL;
            if (sprite->flipVertical) flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
            
            if (entity->hasComponent<TransformComponent>()){
                auto transComp = entity->getComponent<TransformComponent>();
                rot = toAngle(transComp->radian);
            }

            auto texture = textureManager->getTexture(sprite->getTextureId());
            if(!texture){
                texture = textureManager->unknown;
                sprite->textureId = "unknown";
            }
            renderer->render(texture, &srcRect, &dstRect, rot, nullptr, flip);
        }
    }
}


void RenderSystem::drawText(const std::shared_ptr<Entity>& entity) {
    if (!entity->isActive) return;


    if(entity->hasComponent<PositionComponent>() && entity->hasComponent<TextLabelComponent>()){
        auto posComp = entity->getComponent<PositionComponent>();
        auto textComp = entity->getComponent<TextLabelComponent>();

        if (posComp && textComp) {
            SDL_FRect dstRect = {0, 0, textComp->w, textComp->h};
            dstRect.x = posComp->x - (dstRect.w/2);
            dstRect.y = posComp->y - (dstRect.h/2);
            if(cameraEntity){
                auto cameraPos = cameraEntity->getComponent<PositionComponent>();
                if(cameraPos){
                   dstRect.x = dstRect.x - cameraPos->x;                   
                   dstRect.y = dstRect.y - cameraPos->y;
                }
            }

            SDL_RendererFlip flip = SDL_FLIP_NONE;
            float rot = 0.0f;
            renderer->setFont(textComp->font, textComp->size);
            textureManager->loadText(textComp->text.c_str());
            auto texture = textureManager->getTexture(textComp->text.c_str());
            renderer->render(texture, nullptr, &dstRect, rot, nullptr, SDL_FLIP_NONE);
        }
    }
}
