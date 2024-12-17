#include "Systems/RenderSystem.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
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


        auto transform = entity->getComponent<TransformComponent>();
        auto sprite = entity->getComponent<SpriteComponent>();
        if (transform && sprite) {


            // Renderer 통해 그리기
            auto texture = textureManager->getTexture(sprite->getTextureID());

            SDL_Rect srcRect = toSDLRect(sprite->srcRect);
            SDL_Rect dstRect = toSDLRect(sprite->dstRect);
            dstRect.x = static_cast<int>(transform->x());
            dstRect.y = static_cast<int>(transform->y());

            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (sprite->flipHorizontal) flip = SDL_FLIP_HORIZONTAL;
            if (sprite->flipVertical) flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);


            renderer->render(texture, &srcRect, &dstRect, 0.0, nullptr, flip);
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


