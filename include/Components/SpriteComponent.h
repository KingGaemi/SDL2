#pragma once
#include <string>
#include "ECS/Component.h"
#include "Rect.h"
#include <cmath>


class SpriteComponent : public Component{

public:
	std::string textureId;
	Rect srcRect;
	FRect dstRect;
	float originWidth;
	float originHeight;
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	bool flipHorizontal = false;
	bool flipVertical = false;
	float scale = 1.0f;
	bool hasDirectional = false;
	int zIndex = 1;


	SpriteComponent(const std::string& texId, float w, float h, float sc, bool hasDirectional = false) : textureId(texId) , scale(sc), hasDirectional(hasDirectional) {
        w = std::round(w * 10) / 10;
    	h = std::round(h * 10) / 10;
		srcRect = {0, 0, static_cast<int>(w), static_cast<int>(h)};
		dstRect = {0, 0, w*sc, h*sc};
		originWidth = w;
		originHeight = h;
	}

	void toggleFlipHorizontal() {
        flipHorizontal = !flipHorizontal;
    }

    void toggleFlipVertical() {
    	flipVertical = !flipVertical;
    }

	std::string getTextureId() const {
		if(textureId != ""){
			return textureId;	
		}else{
			return "unknown";
		}
	}
	

	
private:
	
};