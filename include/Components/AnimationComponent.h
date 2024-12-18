#pragma once
#include "nlohmann/json.hpp"
#include "ECS/Component.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>



struct AnimationFrame {
    int x, y, w, h;       
    float duration;    // s 
};


struct AnimationData {
    std::string name;     
    std::vector<AnimationFrame> frames;
    bool loop = true;     
};




class AnimationComponent : public Component {
public: 
	using json = nlohmann::json;

	std::string currentAnimation;
	std::map<std::string, AnimationData> animations;

	float currentTime = 0.0f;
	int currentFrameIndex = 0;

	void playAnimation(const std::string animName);
	bool loadAnimationsFromFile(const std::string& filename,std::shared_ptr<AnimationComponent> animComp); 
	AnimationData* getCurrentAnimationData();
	AnimationFrame* getCurrentFrame();
private:


		
};