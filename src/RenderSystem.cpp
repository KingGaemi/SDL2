#include "Systems/RenderSystem.h"
#include "ECS/Entity.h"
#include "Components/PositionComponent.h"
#include "Components/SpriteComponent.h"
#include "Renderer.h"
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

        if(entity->hasComponent<PositionComponent>() && entity->hasComponent<SpriteComponent>()){

            auto posComp = entity->getComponent<PositionComponent>();
            auto sprite = entity->getComponent<SpriteComponent>();
            if (posComp && sprite) {


                // Renderer 통해 그리기
                auto texture = textureManager->getTexture(sprite->getTextureID());

                SDL_Rect srcRect = toSDLRect(sprite->srcRect);
                SDL_Rect dstRect = toSDLRect(sprite->dstRect);
                dstRect.x = static_cast<int>(posComp->x());
                dstRect.y = static_cast<int>(posComp->y());

                SDL_RendererFlip flip = SDL_FLIP_NONE;
                if (sprite->flipHorizontal) flip = SDL_FLIP_HORIZONTAL;
                if (sprite->flipVertical) flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);


                renderer->render(texture, &srcRect, &dstRect, 0.0, nullptr, flip);
            }
        }
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


void RenderSystem::setTextureManager(std::unique_ptr<TextureManager> p_textureManager){

    textureManager = std::move(p_textureManager);
}


