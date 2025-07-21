#pragma once

#include "ecs/System.h"
#include "ecs/Entity.h"
#include "ecs/ECSManager.h"
#include "Groups.h"
#include "Requests.h"
#include "TextureManager.h"
#include "EffectManager.h"

#include <string>
#include <vector>
#include <memory>
#include <cmath>


class Rect;

class Renderer;
// using TextureSize = std::pair<int, int>;

class RenderSystem : public System{

public:

    bool debugMode = false;

	RenderSystem(Renderer& renderer, std::shared_ptr<ECSManager>& ecsManager, std::shared_ptr<EffectManager> effectManager) : renderer(&renderer), textureManager(nullptr), ecsManager(ecsManager), effectManager(effectManager) {}
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
    std::pair<int, int> getTextureSize(const std::string& textureID);
    void setTextureManager(TextureManager& p_textureManager); 
    SDL_FRect toSDLFRect(const FRect& r);
    SDL_Rect toSDLRect(const Rect& r);


protected:
    Renderer* renderer; // SDL_Renderer 래핑 클래스
    TextureManager* textureManager;
    void drawEntity(const std::shared_ptr<Entity>& entity);
    void drawShadow(const std::shared_ptr<Entity>& entity);
    void drawUI(const std::shared_ptr<Entity>& entity);
    void drawText(const std::shared_ptr<Entity>& entity);
    void drawEffects();
    std::shared_ptr<Entity> cameraEntity;
    std::shared_ptr<ECSManager> ecsManager;
    std::shared_ptr<EffectManager> effectManager;
    
    
private:

};