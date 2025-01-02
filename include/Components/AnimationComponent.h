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
	std::string type;
    std::string name;     
    std::vector<AnimationFrame> frames;
    bool loop = true;     
};



using json = nlohmann::json;

class AnimationComponent : public Component {
public:

	std::string currentAnimation;
	std::map<std::string, AnimationData> animations;

	float currentTime = 0.0f;
	int currentFrameIndex = 0;

	float fast = 1.0f;

	float moveFast = 1.0f;
	float attackFast = 1.0f;

	bool busy = false;


	void playAnimation(const std::string animName);
	bool loadAnimationsFromFile(const std::string& filename,std::shared_ptr<AnimationComponent> animComp);
	bool isAnimationComplete() const;

	void saveJson();

	AnimationData* getCurrentAnimationData();
	AnimationFrame* getCurrentFrame();
private:


		
};