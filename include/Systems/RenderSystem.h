#pragma once

#include "ECS/System.h"
#include "TextureManager.h"

#include <vector>
#include <memory>


class Entity;
class Renderer;
// using TextureSize = std::pair<int, int>;

class RenderSystem : public System{

public:
	RenderSystem(Renderer& renderer) : renderer(&renderer) {}
    void update(std::vector<std::shared_ptr<Entity>>& entities, float deltaTime) override;
    std::pair<int, int> getTextureSize(const std::string& textureID);
    void setTextureManager(std::unique_ptr<TextureManager> p_textureManager);
   
private:
	std::unique_ptr<TextureManager> textureManager;
	Renderer* renderer;

};