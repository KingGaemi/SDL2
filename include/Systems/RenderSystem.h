#pragma once

#include "ECS/System.h"
#include "ECS/Entity.h"
#include "ECS/ECSManager.h"
#include "Groups.h"
#include "TextureManager.h"

#include <vector>
#include <memory>


class Rect;

class Renderer;
// using TextureSize = std::pair<int, int>;

class RenderSystem : public System{

public:

    bool debugMode = true;

	RenderSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager) : renderer(&renderer), textureManager(nullptr), ecsManager(ecsManager) {}
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
    std::pair<int, int> getTextureSize(const std::string& textureID);
    void setTextureManager(TextureManager& p_textureManager); 
    SDL_Rect toSDLRect(const Rect& r);

protected:
    Renderer* renderer; // SDL_Renderer 래핑 클래스
    TextureManager* textureManager;
    void drawEntity(const std::shared_ptr<Entity>& entity);
    std::shared_ptr<Entity> cameraEntity;
    std::shared_ptr<ECSManager> ecsManager;
    
private:

};