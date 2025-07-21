#pragma once 
#include "engine/math/Rect.h"
#include "engine/ecs/core/Component.h"


enum class ButoonType{
    Confirm,
    Cancle,
    Play,

};


class ClickableComponent : public Component {


public:

	FRect rect;

	float offsetX, offsetY, w, h;
	bool isClicked = false;
    

	ClickableComponent(float offsetX, float offsetY, float w, float h) : offsetX(offsetX), offsetY(offsetY), w(w), h(h){

		rect.w = w;
		rect.h = h;

	}
	bool isHovered(float posX, float posY, float mouseX, float mouseY) const {
        return mouseX >= (posX + offsetX) - w/2 && mouseX <= (posX + offsetX) + w/2 && mouseY >= (posY + offsetY) - h/2 && mouseY <= (posY + offsetY) + h/2;
    }

    

};