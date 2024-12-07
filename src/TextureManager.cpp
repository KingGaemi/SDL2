#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "TextureManager.h"




TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance(){
	if( instance == nullptr){
		instance = new TextureManager();
	}
	return instance;
}



bool TextureManager::load(std::string_view id, std::string_view p_filePath, Renderer* renderer){


	std::cout << "TextureManager load : " << p_filePath << std::endl;

	if(textureMap.find(std::string(id)) != textureMap.end()){
		std::cerr << "Already loaded texture. ID: " << id << std::endl;
		return false;
	}


	SDL_Texture* texture = renderer->loadTexture(std::string(p_filePath).c_str());
	if (!texture) {

		std::cerr << "Failed to load texture: "<< SDL_GetError() << std::endl;
		return false;
	}else {
    	std::cout << "Successfully loaded texture: " << p_filePath << std::endl;
	}


	textureMap[std::string(id)] = texture;
	return true;

}



SDL_Texture* TextureManager::get(std::string_view id) const {

	auto it = textureMap.find(std::string(id));
	if( it != textureMap.end()) {
		return it->second;
	}


	return nullptr;

}


void TextureManager::clean() {

	for(auto& pair : textureMap){
		SDL_DestroyTexture(pair.second);
	}

	textureMap.clear();

}




TextureManager::~TextureManager(){
	clean();
}


