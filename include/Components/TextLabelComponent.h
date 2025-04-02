#pragma once

#include "ECS/Component.h"
#include <string>

class TextLabelComponent : public Component {
public:
	std::string text;
	std::string font;
	float w, h;
	int size;
	TextLabelComponent(const std::string& text, const std::string& font, int size) : text(text), font(font), size(size){
		h = size*2;
		w = font.length() * 10;
	}
	void setText(const std::string& ptext){
		text = ptext;
		
	}

};