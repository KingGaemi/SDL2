#pragma once
#include "nlohmann/json.hpp"
#include "ECS/Component.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>



struct AnimationFrame {
    int x, y, w, h;       
    float duration;    // s 
};


struct AnimationData {
	std::string type;
    std::string name;     
    std::vector<AnimationFrame> frames;
    bool loop = true;     
};



using json = nlohmann::json;

class AnimationComponent : public Component {
public:

	AnimationComponent(const std::string& filename, const std::string& spriteName) : filename(filename) {
		if(loadAnimationsFromFile(spriteName)){
			//
			std::cout << "Load animation sucesse. :" << filename << std::endl;
		}else{
			std::cout << "Load animation failed. :" << filename << std::endl;
		}
	}

	std::string currentAnimation = "d_idle";
	std::map<std::string, AnimationData> animations;
	float fast = 1.0f;
	float attackFast = 1.0f;
	float moveFast = 2.0f;

	float currentTime = 0.0f;
	int currentFrameIndex = 0;

	bool busy = false;

	
	void playAnimation(const std::string& animName);
	bool loadAnimationsFromFile(const std::string& spriteName);
	bool isAnimationComplete() const;

	AnimationData* getCurrentAnimationData();
	AnimationFrame* getCurrentFrame();
private:
	std::string filename;


		
};