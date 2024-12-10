#include "Components/SpriteComponent.h"
#include <string_view>







SpriteComponent::SpriteComponent(std::string_view id, TransformComponent* transform, Renderer* renderer)
        : textureID(id), transform(transform), renderer(renderer) {}



void SpriteComponent::init(){

	SDL_Texture* texture = TextureManager::getInstance()->get(textureID);
	int width, height;
	// 텍스처의 너비와 높이를 쿼리
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

	// srcRect 설정
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;

}


void SpriteComponent::draw(){

	dstRect.x = static_cast<int>(transform->x());
	dstRect.y = static_cast<int>(transform->y());
	dstRect.w = transform->width * transform->scale;
	dstRect.h = transform->height * transform->scale;

	renderer->draw(textureID, &srcRect, &dstRect);


}



void SpriteComponent::render(){

	
	SDL_Texture* texture = TextureManager::getInstance()->get(textureID);
	if(texture){
		renderer->render(texture, &srcRect, &dstRect);
	}else {

		std::cerr << "Error: Texture not found for ID: " << textureID << std::endl;
	}

}

void SpriteComponent::update(){




}
