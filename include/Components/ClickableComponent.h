#pragma once 
#include "Rect.h"


class ClickableComponent : public Component {


public:

	FRect rect;
	bool isClicked = false;

	ClickableComponent(float x, float y, float w, float h){

		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

	}
	bool isHovered(float mouseX, float mouseY) const {
        return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
    }


};