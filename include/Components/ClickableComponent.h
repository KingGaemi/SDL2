#pragma once 
#include "Rect.h"
#include "ClickCommand.h"



class ClickableComponent : public Component {


public:

	FRect rect;
	bool isClicked = false;
    std::unique_ptr<ClickCommand> onClickCommand;

	ClickableComponent(float x, float y, float w, float h, std::string commandType){

		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		

	}
	bool isHovered(float mouseX, float mouseY) const {
        return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
    }

    void onClick() {
        if (onClickCommand) {
            onClickCommand->execute();
        }
    }

};