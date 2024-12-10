#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <iostream>
#include "IRenderer.h"



class SDL_Texture;
class SDL_Rect;

class TextureManager
{
public:

	static TextureManager*getInstance();
	bool load(std::string_view id, std::string_view p_filePath, IRenderer* renderer);

	SDL_Texture* get(std::string_view id) const;
	void clean();


private:
	static TextureManager* instance;
	std::unordered_map<std::string, SDL_Texture*> textureMap;

	TextureManager() = default;
	~TextureManager();       

};    