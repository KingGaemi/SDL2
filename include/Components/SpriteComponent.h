#pragma once
#include <string>
#include "ECS/Component.h"
#include "TextureManager.h"
#include "Components/TransformComponent.h"
#include "Renderer.h"


class SpriteComponent : public DrawableComponent{

public:
	std::string textureID;
	TransformComponent* transform;
	Renderer* renderer;

	SpriteComponent(std::string_view id, TransformComponent* transform, Renderer* renderer);
	void init() override;
	void draw() override;
	void render();
	void update() override;

	SDL_Rect srcRect;
	SDL_Rect dstRect;        

private:
	std::string path;
	

};