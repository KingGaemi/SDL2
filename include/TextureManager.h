#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include <utility>  // for std::pair
#include "Renderer.h"


class TextureManager{
public:

	TextureManager(Renderer& renderer) : renderer(&renderer) {
		unknown = renderer.loadTexture("res/gfx/unknown.png");
	}
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

	SDL_Texture* getTexture(const std::string& textureId) {
		// std::cout << "TextureManager :: getTexture(" << textureId << ")" << std::endl;
		auto it = textures.find(textureId);
		if (it != textures.end()) {
			// std::cout << "getTexture Success" << std::endl;
            return it->second;
        }
        std::cerr << "Failed to get texture: (" << textureId << ")" << std::endl;
        // it = textures.find("unknown");
           	    
        // return it->second;
        return nullptr;
	}

	std::pair<int, int>  getTextureResolution(const std::string& textureID) {
		// std::cout << "TextureManager :: getTexture(" << textureID << ")" << std::endl;
		auto it = textures.find(textureID);

		int width = 0, height = 0;
		if (it != textures.end()) {
			// std::cout << "getTexture Success" << std::endl;    
		    if (SDL_QueryTexture(it->second, nullptr, nullptr, &width, &height) == 0) {
		        // std::cout << textureID << " : " << width << " x " << height << std::endl;
		    } else {
		        std::cerr << "SDL_QueryTexture Error: " << SDL_GetError() << std::endl;
		        return{-1, -1};
		    }
		   
	    }
	    return {width, height};
	}

	bool loadText(const char * textString){
		SDL_Texture* texture = renderer->loadText(textString);
		if (!texture) {
            std::cerr << "Failed to load textTexture: " << textString << " Error: " << SDL_GetError() << std::endl;
            return false;
        }
		textures["damageText"] = texture;
		return true;
	}

	void cleanup(){
		for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
        textures.clear();
	}

	SDL_Texture* unknown; 
private:
	Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> textures;
	   
};    