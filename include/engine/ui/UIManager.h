#pragma once

#include <vector>
#include "engine/math/Rect.h"


class SDL_Texture*

struct UIElement {
    SDL_Texture* SDL_texture;
    Rect srcRect; 
    Rect dstRect; 
};




class UIManager {


public:

	void addElement(const UIElement& elem) {
        elements.push_back(elem);
    }




private:


	std::std::vector<UIElement> UIElements;




};