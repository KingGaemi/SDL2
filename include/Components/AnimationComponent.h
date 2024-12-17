#pragma once
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

	std::string currentAnimation;
	std::map<std::string, AnimationData> animations;

	float currentTime = 0.0f;
	int currentFrameIndex = 0;

	void playAnimation(const std::string animName){
		if (animations.find(animName) != animations.end()) {
            currentAnimation = animName;
            currentFrameIndex = 0;
            currentTime = 0.0f;
        }else{
        	std::cout << "Has no Animation named:" << animName << "." << std::endl;
        }

	}

	AnimationData* getCurrentAnimationData() {
		auto it = animations.find(currentAnimation);
		if(it != animations.end()){
			return &it->second;
		}
		return nullptr;
	}

	AnimationFrame* getCurrentFrame(){
		AnimationData* data = getCurrentAnimationData();
        if (data && currentFrameIndex >= 0 && currentFrameIndex < (int)data->frames.size()) {
            return &data->frames[currentFrameIndex];
        }
        return nullptr;
	}

private:


		
};