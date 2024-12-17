#pragma once
#include <string>
#include "ECS/Component.h"


struct Rect {
    int x, y, w, h;
};


class SpriteComponent : public Component{

public:

	std::string textureID;
	Rect srcRect;
	Rect dstRect;
	bool flipHorizontal = false;
	bool flipVertical = false;
	float scale;


	SpriteComponent(const std::string& texID, int w, int h, float sc = 1.0f) : textureID(texID) , scale(sc) {
		srcRect = {0, 0, w, h};
		dstRect = {0, 0, (int)(w*sc), (int)(h*sc)};
	}

	void toggleFlipHorizontal() {
        flipHorizontal = !flipHorizontal;
    }

    void toggleFlipVertical() {
    	flipVertical = !flipVertical;
    }

	std::string getTextureID() const {return textureID;}
	

	
private:
	
};