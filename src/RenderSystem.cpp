#include "Systems/RenderSystem.h"
#include "Renderer.h"
#include "Groups.h"
#include "Components/PositionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/Transformcomponent.h"
#include "Components/FloatingEffectComponent.h"
#include "Components/CameraComponent.h"
#include <iostream>


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

    for (auto& entity : entities) {

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
            SDL_Rect dstRect = toSDLRect(sprite->dstRect);

            float offsetY = 0.0f; // for floating effect
            if(entity->hasComponent<FloatingEffectComponent>()) {
                offsetY = entity->getComponent<FloatingEffectComponent>()->renderOffsetY;
            }

            int worldX = static_cast<int>(posComp->x) - (dstRect.w/2);
            int worldY = static_cast<int>(posComp->y + offsetY) - (dstRect.h/2);

            int screenX, screenY;
            screenX = worldX;
            screenY = worldY;
            if(cameraEntity){
                auto camera = cameraEntity->getComponent<CameraComponent>();
                if(camera){
                   screenX = worldX - camera->x;
                   screenY = worldY - camera->y;
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
        if (entity->hasComponent<ColliderComponent>()) {
            auto collider = entity->getComponent<ColliderComponent>();
            
            // collider 위치(월드 좌표) -> 화면 좌표 변환
            // (camX, camY) 만큼 빼주기, 혹은 camTransform 적용
            SDL_Rect debugRect;
            debugRect.x = static_cast<int>(collider->collider.x);
            debugRect.y = static_cast<int>(collider->collider.y);
            debugRect.w = static_cast<int>(collider->collider.w);
            debugRect.h = static_cast<int>(collider->collider.h);
            
            // 원하는 색상 설정 (빨간색, 투명도 255)
            renderer->SetRenderDrawColor(255, 0, 0, 255);
            renderer->RenderDrawRect(debugRect);
        }
    }
}

