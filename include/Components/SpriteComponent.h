#pragma once
#include <string>
#include "ECS/Component.h"
#include "Rect.h"


class SpriteComponent : public Component{

public:

	std::string textureId;
	Rect srcRect;
	FRect dstRect;
	bool flipHorizontal = false;
	bool flipVertical = false;
	float scale = 1.0f;
	bool hasDirectional = false;


	SpriteComponent(const std::string& texId, int w, int h, float sc, bool hasDirectional = false) : textureId(texId) , scale(sc), hasDirectional(hasDirectional) {
		srcRect = {0, 0, w, h};
		dstRect = {0, 0, w*sc, h*sc};
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