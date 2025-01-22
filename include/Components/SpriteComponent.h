#pragma once
#include <string>
#include "ECS/Component.h"
#include "Rect.h"


class SpriteComponent : public Component{

public:

	std::string textureID;
	Rect srcRect;
	Rect dstRect;
	bool flipHorizontal = false;
	bool flipVertical = false;
	float scale = 1.0f;
	bool hasDirectional = false;


	SpriteComponent(const std::string& texID, int w, int h, float sc, bool hasDirectional = false) : textureID(texID) , scale(sc), hasDirectional(hasDirectional) {
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