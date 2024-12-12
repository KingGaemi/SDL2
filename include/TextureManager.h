#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include "Renderer.h"


class TextureManager{
public:

	TextureManager(Renderer& renderer) : renderer(&renderer) {}
	~TextureManager() { cleanup(); }

	bool loadTexture(const std::string& textureID, std::string_view p_filePath){

		SDL_Texture* texture = renderer->loadTexture(std::string(p_filePath).c_str());
		if (!texture) {
            std::cerr << "Failed to load texture: " << p_filePath << " Error: " << IMG_GetError() << std::endl;
            return false;
        }

		textures[textureID] = texture;

		return true;

	};

	SDL_Texture* getTexture(const std::string& textureID) {

		// std::cout << "TextureManager :: getTexture(" << textureID << ")" << std::endl;
		auto it = textures.find(textureID);
		if (it != textures.end()) {
			// std::cout << "getTexture Success" << std::endl;
            return it->second;
        }
        std::cout << "Failed to find Texture.  ID: " << textureID << std::endl;


        return nullptr;

	}
	void cleanup(){

		for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
        textures.clear();
	}


private:
	Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> textures;
	   
};    