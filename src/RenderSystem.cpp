#include "Systems/RenderSystem.h"
#include "ECS/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Renderer.h"
#include <iostream>


void RenderSystem::update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) {
    // 화면 클리어
    renderer->clear();

    
    for (auto& entity : entities) {
        // 렌더링에 필요한 컴포넌트를 가진 엔티티만 처리
        auto transform = entity->getComponent<TransformComponent>();
        auto sprite = entity->getComponent<SpriteComponent>();
        if (transform && sprite) {
            // SDL_Rect srcRect;
            SDL_Rect dstRect;

            // srcRect.w = sprite->width;
            // srcRect.h = sprite->height;
            dstRect.x = static_cast<int>(transform->x());
            dstRect.y = static_cast<int>(transform->y());
            dstRect.w = static_cast<int>(sprite->width * sprite->scale);
            dstRect.h = static_cast<int>(sprite->height * sprite->scale);



            // Renderer 통해 그리기
            auto texture = textureManager->getTexture(sprite->getTextureID());
            // if(texture){
            //     std::cout << "RenderSystem::update() srcRect.w : " << srcRect.w << "dstRect.w : " << dstRect.w << std::endl;
            // }else{
            //     std::cout << "getTexture Failed" << std::endl;
            // }

            renderer->render(texture, NULL, &dstRect);
        }
    }
    // std::cout << "RenderSystem update()" << std::endl;
    // 화면 업데이트
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


